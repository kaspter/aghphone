#ifndef __GLOBALS_H__INCLUDED__
#define __GLOBALS_H__INCLUDED__

namespace agh {

/** According to RFC3551
 *  See http://www.ietf.org/rfc/rfc3551.txt
 */
struct AudioCodec {
	enum {
		PCMU = 0,
		RESERVED1,
		RESERVED2,
		GSM,
		G723,
		DVI4_8000,
		DVI4_16000,
		LPC,
		PCMA,
		G722,
		L16_STEREO,
		L16_MONO,
		QCELP,
		CN,
		MPA,
		G728,
		DVI4_11025,
		DVI4_22050,
		G729,
		RESERVED3
	};
};

int audioCodecClockRate[] = {
		8000,
		0,
		0,
		8000,
		8000,
		8000,
		16000,
		8000,
		8000,
		8000,
		44100,
		44100,
		8000,
		8000,
		90000,
		8000,
		11025,
		22050,
		8000,
		0
};

int audioCodecChannels[] = {
		1,
		0,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		2,
		1,
		1,
		1,
		2,
		1,
		1,
		1,
		1,
		0
};

} /* namespace agh */

#endif /* __GLOBALS_H__INCLUDED__ */
