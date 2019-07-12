#ifndef _DVRNG_h
#define _DVRNG_h

#include "CURandRTC_api.h"
#include "DeviceViewable.h"

class CURAND_RTC_API DVRNG : public DeviceViewable
{
public:
	static DVRNG& singlton();

	virtual std::string name_view_cls() const;
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
	DVRNG_Multi() : m_rng(DVRNG::singlton()) {}

	virtual std::string name_view_cls() const
	{
		return m_rng.name_view_cls();
	}
	
	virtual ViewBuf view() const
	{
		return m_rng.view();
	}

private:
	DVRNG& m_rng;
};

#endif
