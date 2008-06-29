#include "dummycodec.h"
#include <string.h>

namespace agh {

DummyCodec::DummyCodec()
{
}

DummyCodec::~DummyCodec()
{
}

int DummyCodec::getDelay()
{
	return 20;
}

int DummyCodec::getFrameCount()
{
	return 160;
}

int DummyCodec::getFrameSize()
{
	return 2;
}

float DummyCodec::getFrequency()
{
	return 8000.0;
}

int DummyCodec::encode(char *dest, char *src)
{
	int size = getFrameCount()*getFrameSize();
	
	memcpy(dest, src, size);
	
	return size;
}

int DummyCodec::decode(char *dest, char *src, int srcsize)
{
	memcpy(dest, src, srcsize);
	
	return srcsize;
}

} /* namespace agh */
