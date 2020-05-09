import os
import sys
import site
from cffi import FFI

ffi  = FFI()

ffi.cdef("""    
void* n_dvrng_create();
""")

if os.name == 'nt':
    fn_curandrtc = 'PyCURandRTC.dll'
elif os.name == "posix":
    fn_curandrtc = 'libPyCURandRTC.so'

if os.name == 'nt':
    os.environ["PATH"] += ";"+sys.prefix+"/Fei/"
path_curandrtc = sys.prefix+"/Fei/"+fn_curandrtc
if not os.path.isfile(path_curandrtc):
    if os.name == 'nt':
        os.environ["PATH"] += ";"+site.USER_BASE+"/Fei/"	
    path_curandrtc = site.USER_BASE+"/Fei/"+fn_curandrtc
    if not os.path.isfile(path_curandrtc):
        path_curandrtc = os.path.dirname(__file__)+"/"+fn_curandrtc

native = ffi.dlopen(path_curandrtc)

import ThrustRTC as trtc

class DVRNG(trtc.DeviceViewable):
	def __init__(self):
		self.m_cptr = native.n_dvrng_create()

