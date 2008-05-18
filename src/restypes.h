#ifndef __RESTYPES_H__INCLUDED__
#define __RESTYPES_H__INCLUDED__

namespace agh {

struct RequestConnectResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENED_YET,
		BUSY,
		REJECTED,
		
		OTHER = -1
	};
};

struct SetCodecResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		NO_SUCH_CODEC,
		NOT_SUPPORTED,
		
		OTHER = -1
	};
};

struct SetDestinationPortResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		OUT_OF_RANGE,
		
		OTHER = -1
	};
};

struct StartTransmissionResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		NOT_CONNECTED,
		
		OTHER = -1
	};
};

struct DisconnectResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		
		OTHER = -1
	};
};

struct DisconnectReason {
	enum {
		USER_REQUESTED,
		POOR_QUALITY,
		
		OTHER = -1
	};
};

struct ConnectResult {
	enum {
		SUCCESS = 0,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		INVALID_HOST,
		ALREADY_CONNECTED,
		REJECTED,
		BUSY,
		
		OTHER = -1
	};
};

struct NegotiateResult {
	enum {
		SUCCESS,
		INTERNAL_ERROR,
		NOT_IMPLEMENTED_YET,
		MUTUALLY_DISCRAPENCY,
		
		OTHER = -1
	};
};

}

#endif /* __RESTYPES_H__INCLUDED__ */
