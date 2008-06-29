#include "ringbuffer.h"

namespace agh {

RingBuffer::RingBuffer(long size, int packetSize)
{
	writeCursor = 0;
	readCursor = 0;
	readyCount = 0;
	bufferSize = size;
	this->sampleSize = sampleSize;
	buffer = new char[size];
}

RingBuffer::~RingBuffer()
{
	delete buffer;
}
	
bool RingBuffer::putData(char *data, long size)
{
	if( bufferSize - getReadyCount() <= size )
		return false; 
	
	char *ptr1 = buffer + writeCursor*sampleSize;
	char *ptr2 = data;
	
	long toEnd = bufferSize - writeCursor;
	
	if(toEnd >= size) {
		for(long i=0;i<toEnd*sampleSize;i++) *ptr1++ = *ptr2++;
	} else {
		for(long i=0;i<toEnd*sampleSize;i++) *ptr1++ = *ptr2++;
		ptr1 = buffer;
		for(long i=0;i<(size-toEnd)*sampleSize;i++) *ptr1++ = *ptr2++;	
	}
	
	writeCursor += size;
	if( writeCursor >= bufferSize )
		writeCursor -= bufferSize;
				
	readyCount += size;
	
	return true;
}

bool RingBuffer::getData(char *data, long size)
{
	if( getReadyCount() <= size )
		return false; 
	
	char *ptr1 = buffer + readCursor*sampleSize;
	char *ptr2 = data;
	
	long toEnd = bufferSize - readCursor;
	
	if(toEnd >= size) {
		for(long i=0;i<toEnd*sampleSize;i++) *ptr2++ = *ptr1++;
	} else {
		for(long i=0;i<toEnd*sampleSize;i++) *ptr2++ = *ptr1++;
		ptr1 = buffer;
		for(long i=0;i<(size-toEnd)*sampleSize;i++) *ptr2++ = *ptr1++;	
	}
	
	readCursor += size;
	if( readCursor >= bufferSize )
		readCursor -= bufferSize;
				
	readyCount -= size;
	
	return true;
}

long RingBuffer::getReadyCount()
{
	return readyCount;
}
	
} /* namespace agh */
