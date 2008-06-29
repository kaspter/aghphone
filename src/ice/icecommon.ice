module agh {

	exception VoipException {
	};
	
	exception TerminalBusyException extends VoipException {
	};
	
	exception ConnectionRejectedException extends VoipException {
	};

	struct ICodec {
		int id;
	};

	sequence<ICodec> Codecs;

	struct CallParameters {
		ICodec outgoingCodec;
		ICodec incomingCodec;
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
