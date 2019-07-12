#include "TRTCContext.h"
#include "cuda_inline_headers.hpp"
#include "cuda_wrapper.h"
#include "DVRNG.h"
#include "xor_wow_data.hpp"
#include "curandrtc_built_in.h"

void CURandRTC_Init()
{
	static bool s_initialized = false;
	if (!s_initialized)
	{
		if (!init_cuda())
		{
			printf("Cannot find CUDA driver. Exiting.\n");
			exit(0);
		}
		TRTC_Add_Built_In_Header(s_name_headers[0], s_content_headers[0]);
		TRTC_Add_Inlcude_Filename(s_name_headers[0]);
		s_initialized = true;
	}
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

std::string DVRNG::name_view_cls() const
{
	return "RNG";
}

ViewBuf DVRNG::view() const
{
	ViewBuf ret(sizeof(RNG));
	((RNG*)ret.data())->d_offset_matrix = m_offset_matrix;
	((RNG*)ret.data())->d_sequence_matrix = m_sequence_matrix;
	return ret;
}
