#include "codecfactory.h"

#include "dummycodec.h"

namespace agh {

CodecFactory::CodecFactory()
{
}

CodecFactory::~CodecFactory()
{
}

Codec& CodecFactory::getCodec(int id)
{
	Codec *retCodec = NULL;
	
	switch(id) {
	default:
		if( instanceMap.find(-1) == instanceMap.end() )
			instanceMap[-1] = new DummyCodec();
		retCodec = instanceMap[-1];
		break;
	}
	
	return *retCodec;
}

} /* namespace agh */
