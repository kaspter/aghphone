module agh {
	
	sequence<int> prefferedCodecs;
	
	interface ISlave {
		int remoteConnect();
		int remoteDisconnect(int reason);
		
		int remotePing();
		
		prefferedCodecs remoteGetPrefferedOutgoingCodec();
		prefferedCodecs remoteGetPrefferedIncomingCodec();
		int remoteSetOutgoingCodec(int codec);
		int remoteResetOutgoingCodec(int codec);
		
		int remoteSetDestinationPort(int port);
		int remoteGetDestinationPort(int port);
		int remoteGetSourcePort();
		
		int remoteStartTransmission();
	};

};

