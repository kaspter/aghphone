module agh {
	
	interface ISlaveCallback {
		int disconnect(int reason);
	};

	dictionary<int, int> CodecsMap;
	
	interface ISlave {
		int requestConnect();
		CodecsMap getAvailableCodecs();
		int setCodec(int codec);
		int setDestinationPort(int port);
		int getSourcePort();
		int startTransmission();
		int disconnect(int reason);
		void setCallback(ISlaveCallback *callback);
		int resetCodec(int codec);
		ISlaveCallback* getCallback();
	};

};

