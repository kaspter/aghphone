module agh {

	exception VoipException {
	};
	
	exception TerminalBusyException extends VoipException {
	};
	
	exception ConnectionRejectedException extends VoipException {
	};

	struct Codec {
		int id;
	};

	sequence<Codec> Codecs;

	struct CallParameters {
		Codec outgoingCodec;
		Codec incomingCodec;
		int masterRtpPort;
	};

	struct CallParametersResponse {
		int slaveRtpPort;
	};

	struct TerminalCapabilities {
		Codecs preferredOutgoingCodecs;
		Codecs preferredIncomingCodecs;
	};

	struct TerminalAddress {
		string ipAddress;
		string port;
		string name;
	};
	
};
