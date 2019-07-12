#include "JCURandRTC_Native.h"
#include "DVRNG.h"

JNIEXPORT jlong JNICALL Java_JCURandRTC_Native_dvrng_1create(JNIEnv *, jclass)
{
	return (jlong)(new DVRNG_Multi);
}

