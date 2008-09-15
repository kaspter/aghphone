#include <Ice/Identity.ice>
#include "icecommon.ice"

module agh {

	interface IMasterCallback {
	
		void remoteTryConnectAck(CallParametersResponse response);	
		void remoteTryConnectNack();
	};
	
	interface IMixer {
		void foo();
	};
	
	interface ISlave {
		
		TerminalCapabilities remoteGetCapabilities();
		
		void remoteTryConnect(CallParameters parameters, ::Ice::Identity masterIdent)
								throws TerminalBusyException, ConnectionRejectedException;
		
		void remoteStartTransmission();
		
		void remoteDisengage();
		
		int remotePing();
	
	};

};
