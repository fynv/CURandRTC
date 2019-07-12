import PyCURandRTC as native
import ThrustRTC as trtc

class DVRNG(trtc.DeviceViewable):
	def __init__(self):
		self.m_cptr = native.n_dvrng_create()



