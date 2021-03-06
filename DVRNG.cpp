#include "TRTCContext.h"
#include "cuda_inline_headers.hpp"
#include "cuda_wrapper.h"
#include "DVRNG.h"
#include "xor_wow_data.hpp"
#include "curandrtc_built_in.h"

static bool CURandRTC_Init(bool istrying=false)
{
	static bool s_initialized = false;
	if (!s_initialized)
	{
		if (!init_cuda())
		{
			printf("Cannot find CUDA driver. \n");
			if (istrying) return false;
			else exit(0);
		}
		TRTC_Add_Built_In_Header(s_name_headers[0], s_content_headers[0]);
		TRTC_Add_Inlcude_Filename(s_name_headers[0]);
		s_initialized = true;
	}
	return s_initialized;
}

bool CURandRTC_Try_Init()
{
	if (!TRTC_Try_Init()) return false;
	return CURandRTC_Init(true);
}

DVRNG::DVRNG()
{
	CURandRTC_Init();

	{
		CUdeviceptr dptr;
		cuMemAlloc(&dptr, sizeof(unsigned) * 6400);
		m_sequence_matrix = (unsigned*)dptr;
		cuMemcpyHtoD(dptr, xorwow_sequence_matrix, sizeof(unsigned) * 6400);
	}

	{
		CUdeviceptr dptr;
		cuMemAlloc(&dptr, sizeof(unsigned) * 6400);
		m_offset_matrix = (unsigned*)dptr;
		cuMemcpyHtoD(dptr, xorwow_offset_matrix, sizeof(unsigned) * 6400);
	}

	m_name_view_cls = "RNG";
}

DVRNG::~DVRNG()
{
	cuMemFree((CUdeviceptr)m_sequence_matrix);
	cuMemFree((CUdeviceptr)m_offset_matrix);
}


DVRNG& DVRNG::singlton()
{
	static DVRNG _singlton;
	return _singlton;
}

ViewBuf DVRNG::view() const
{
	ViewBuf ret(sizeof(RNG));
	((RNG*)ret.data())->d_offset_matrix = m_offset_matrix;
	((RNG*)ret.data())->d_sequence_matrix = m_sequence_matrix;
	return ret;
}
