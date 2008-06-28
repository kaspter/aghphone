module agh {

	exception VoipException {};
	
	struct StreamAddress {
		string ipAddress;
		string port;
	};
	
	struct TerminalAddress {
		string ipAddress;
		string port;
		string name;
	};
	
	struct AudioCodec {
		int id;
		int bitrate;
		int priority;
	};
	
	struct CallParameter {
		AudioCodec codec;
		StreamAddress slaveRTPAddress;
		StreamAddress slaveRTCPAddress;
	};

	sequence<CallParameter> CallParameters;
};
