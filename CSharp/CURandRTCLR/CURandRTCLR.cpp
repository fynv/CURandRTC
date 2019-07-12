#include "CURandRTCLR.h"
#include "DVRNG.h"

namespace CURandRTCLR
{
	IntPtr Native::dvrng_create()
	{
		return (IntPtr)(new DVRNG_Multi);
	}
}
