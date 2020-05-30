import os
import sys
import site
import ThrustRTC as trtc
from cffi import FFI

ffi  = FFI()

ffi.cdef("""    
void* n_dvrng_create();
""")

if os.name == 'nt':
    fn_curandrtc = 'PyCURandRTC.dll'
elif os.name == "posix":
    fn_curandrtc = 'libPyCURandRTC.so'

path_curandrtc = os.path.dirname(__file__)+"/"+fn_curandrtc

native = ffi.dlopen(path_curandrtc)

class DVRNG(trtc.DeviceViewable):
	def __init__(self):
		self.m_cptr = native.n_dvrng_create()

