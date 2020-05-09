#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define PY_CURANDRTC_API __declspec(dllexport)
#else
#define PY_CURANDRTC_API 
#endif

extern "C"
{
	PY_CURANDRTC_API void* n_dvrng_create();
}

#include "DVRNG.h"

void* n_dvrng_create()
{
	return new DVRNG_Multi;
}
