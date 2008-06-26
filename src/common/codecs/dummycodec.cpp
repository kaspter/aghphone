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
	return 16;
}

float DummyCodec::getFrequency()
{
	return 8000.0;
}

long DummyCodec::encode(void *dest, void *src)
{
	int size = getFrameCount()*getFrameSize();
	
	memcpy(dest, src, size);
	
	return size;
}

long DummyCodec::decode(void *dest, void *src)
{
	int size = getFrameCount()*getFrameSize();
	
	memcpy(dest, src, size);
	
	return size;
}

} /* namespace agh */
