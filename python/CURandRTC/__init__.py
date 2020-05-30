import os
import sys
import site
import ThrustRTC as trtc
from cffi import FFI

ffi  = FFI()

ffi.cdef("""
int n_curandrtc_try_init(); 
void* n_dvrng_create();
""")

if os.name == 'nt':
    fn_curandrtc = 'PyCURandRTC.dll'
elif os.name == "posix":
    fn_curandrtc = 'libPyCURandRTC.so'

path_curandrtc = os.path.dirname(__file__)+"/"+fn_curandrtc

native = ffi.dlopen(path_curandrtc)

if native.n_curandrtc_try_init()==0:
	raise ImportError('cannot import CURandRTC')


class DVRNG(trtc.DeviceViewable):
	def __init__(self):
		self.m_cptr = native.n_dvrng_create()

