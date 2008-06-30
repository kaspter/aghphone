#include <cc++/address.h>
#include <time.h>

#define ISQUIET(x) x < -100

#include "mixercore.h"
#include "transport.h"

namespace agh {
	
char sgn(char x) {
	if (x < 0) return -1;
	else if (x == 0) return 0;
	else return 1;
}

MixerCore::MixerCore(map<string, TerminalInfo*>* remoteHosts) {
	this->remoteHosts = remoteHosts;
	this->buffer = new RingBuffer(1024*1024*100, 1);
	
	this->receiver = new MixerCoreReceiver(remoteHosts, buffer);
	this->transmitter = new MixerCoreTransmitter(remoteHosts, buffer);
	this->transmitter->start();
	this->receiver->start();
}

MixerCoreReceiver::MixerCoreReceiver(map<string, TerminalInfo*>* remoteHosts, RingBuffer *buffer) {
	this->remoteHosts = remoteHosts;
	this->buffer = buffer;
}

MixerCoreTransmitter::MixerCoreTransmitter(map<string, TerminalInfo*>* remoteHosts, RingBuffer *buffer) {
	this->remoteHosts = remoteHosts;
	this->buffer = buffer;
}

struct timeval czas_start;

void printTime() {
	struct timeval czas_teraz;
	
	gettimeofday(&czas_teraz, NULL);
	
	printf("%3ld.%3ld [s] \n", czas_teraz.tv_sec - czas_start.tv_sec, czas_teraz.tv_usec/1000); 
}

void MixerCoreReceiver::run() {
	
	char *buf = new char[1024*1024*100];
	
	TimerPort::setTimer(10);
	while(1) {
		// Get data from all incoming streams
		map<string, TerminalInfo*>::iterator iter;
		
		// read data
		int index = 0;
		for( iter = remoteHosts->begin(); iter != remoteHosts->end(); iter++ ) {

			TerminalInfo* info = iter->second;
			if (info == NULL) {
				continue;
			}
					
			Transport *transport = info->transport;
					
			if (transport == NULL) {
				continue;
			}
					
			info->readedSize = transport->recv(buf);
			
			cout << "[" << index << "] trying to read\n";
			if (info->readedSize > 0) {
				info->buf->putData(buf, info->readedSize);
				cout << "[" << index << "] packet has been read\n";
			}
			
			index++;
		}	
		
		Thread::sleep(TimerPort::getTimer());
		TimerPort::incTimer(10);
	}
}

void MixerCoreTransmitter::run() {
	
	char *buf = new char[1024*1024*100];
	int packetSize = 320;
	
	gettimeofday(&czas_start, NULL);
	TimerPort::setTimer(20);
	while(1) {
		
		if (this->buffer->getReadyCount() > packetSize) {
			this->buffer->getData(buf, packetSize);
		
			// send
			map<string, TerminalInfo*>::iterator iter;
			for( iter = remoteHosts->begin(); iter != remoteHosts->end(); iter++ ) {
			
				TerminalInfo* info = iter->second;
				if (info == NULL) {
					continue;
				}
					
				Transport *transport = info->transport;
				if (transport == NULL) {
					continue;
				}
						
				transport->send(buf, packetSize);
				transport->flush();
			}
			
// 			printTime();
		}
		
		Thread::sleep(TimerPort::getTimer());
		TimerPort::incTimer(20);
	}	
}

/**
 * 
 */
void MixerCore::run() {

	char** bufs = new char*[10];
	int packetSize = 320;
	int minPackThreshold = 2;
	int maxPackThreshold = 6;
	int count = 0;
	int available = 0;
	char* overallBuf = new char[1024*1024];
	
	for (int i = 0; i < 10; i++) {
		bufs[i] = new char[1024*1024];
	}
	
	TimerPort::setTimer(10);
	while(1) {
		
		// Get data from all incoming streams
		map<string, TerminalInfo*>::iterator iter;
		
		// read data
		available = 1;
		int index = 0;
		for( iter = remoteHosts->begin(); iter != remoteHosts->end(); iter++ ) {
			TerminalInfo* info = iter->second;
			if (info == NULL || info->buf == NULL) {
				continue;
			}
			
// 			if (info->buf->getReadyCount() > packetSize*minPackThreshold ) {
// 				cout << "[" << index << "]max threshold, ready: " << info->buf->getReadyCount() << endl;
// 				info->buf->skipData(packetSize*minPackThreshold);
// 				cout << "[" << index << "]max threshold, after: " << info->buf->getReadyCount() << endl;
// 			}
			
			if (info->buf->getReadyCount() < packetSize*minPackThreshold ) {
				cout << "[" << index << "]too little skipping\n";
				available = 0;
			}
			index++;
		}	
		
		count = 0;
		if (available)  {
			// read data
			for( iter = remoteHosts->begin(); iter != remoteHosts->end(); iter++ ) {
				TerminalInfo* info = iter->second;
				if (info == NULL || info->buf == NULL) {
					continue;
				}
				if (info->buf->getReadyCount() > packetSize) {
					info->buf->getData(bufs[count],packetSize);
					count++;
				}
			}
		}
		
		if (count > 0) {
			// mix original solution
			for (int i = 0; i < packetSize; i++) {
				overallBuf[i] = 0; 
				int pCount = count;
				for (int j = 0; j < count; j++) {
					if (ISQUIET(bufs[j][i])) pCount--;
					else overallBuf[i] += bufs[j][i];
				}
				if (pCount != 0)
					overallBuf[i] /= pCount;
			}
			
// 			// mix Align-to-Average Weighted AAW
// 			for (int i = 0; i < packetSize; i++) {
// 				overallBuf[i] = 0; 
// 				for (int j = 0; j < count; j++) {
// 					overallBuf[i] += bufs[j][i];
// 				}
// 				overallBuf[i] /= count;
// 			}
			
// 			// mix Align-to-Greatest Weighted AGW
// 			char totalMax = 0;
// 			char mixedMax = 0;
// 			for (int i = 0; i < packetSize; i++) {
// 				overallBuf[i] = 0; 
// 				for (int j = 0; j < count; j++) {
// 					if (bufs[j][i] > totalMax) totalMax = bufs[j][i];
// 					overallBuf[i] += bufs[j][i];
// 				}
// 				overallBuf[i] /= count;
// 				if (overallBuf[i] > mixedMax) mixedMax = overallBuf[i];
// 			}
// 			char u = 1; // factor used to adjust the amplitude
// 			for (int i = 0; i < packetSize; i++) {
// 				overallBuf[i] = overallBuf[i]*u*totalMax/mixedMax;
// 			}
			
// 			// mix Align-to-Self Weighted ASW
// 			for (int i = 0; i < packetSize; i++) {
// 				overallBuf[i] = 0; 
// 				char sum = 0;
// 				for (int j = 0; j < count; j++) {
// 					overallBuf[i] += bufs[j][i]*bufs[j][i]*sgn(bufs[j][i]);
// 					sum += abs(bufs[j][i]);
// 				}
// 				overallBuf[i] /= sum;
// 			}
			
// 			// mix Align-to-Energy Weighted AEW
// 			for (int i = 0; i < packetSize; i++) {
// 				overallBuf[i] = 0; 
// 				char sum = 0;
// 				for (int j = 0; j < count; j++) {
// 					overallBuf[i] += bufs[j][i]*bufs[j][i]*bufs[j][i];
// 					sum += abs(bufs[j][i])*abs(bufs[j][i]);
// 				}
// 				overallBuf[i] /= sum;
// 			}
			
			buffer->putData(overallBuf, packetSize);
			cout << "putted in buffor" << endl;
		}
				
		Thread::sleep(TimerPort::getTimer());
		TimerPort::incTimer(10);
	}
}

} // namespace
