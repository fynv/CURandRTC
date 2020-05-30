#ifndef _DVRNG_h
#define _DVRNG_h

#include "CURandRTC_api.h"
#include "DeviceViewable.h"

bool CURAND_RTC_API CURandRTC_Try_Init();

class CURAND_RTC_API DVRNG : public DeviceViewable
{
public:
	static DVRNG& singlton();
	virtual ViewBuf view() const;

private:
	DVRNG();
	~DVRNG();

	unsigned* m_sequence_matrix;
	unsigned* m_offset_matrix;
};

// for use-cases where singlton is not acceptable
class CURAND_RTC_API DVRNG_Multi : public DeviceViewable
{
public:
	DVRNG_Multi() : m_rng(DVRNG::singlton()) 
	{
		m_name_view_cls = m_rng.name_view_cls();
	}
	
	virtual ViewBuf view() const
	{
		return m_rng.view();
	}

private:
	DVRNG& m_rng;
};

#endif
