# example showing how to separate init and call

import ThrustRTC as trtc
import CURandRTC as rndrtc

rng = rndrtc.DVRNG()

ker_init = trtc.For(['rng','states'], 'idx',
	'''
	rng.state_init(1234, idx, 0, states[idx]);
	''')

ker_call = trtc.For(['states', 'vec_rnd'], 'idx',
	'''
	vec_rnd[idx]=(float)states[idx].rand01();
	'''
	)

rng_states = trtc.device_vector('RNGState', 1024)
d_vec_rnd = trtc.device_vector('float', 1024)

ker_init.launch_n(1024, [rng, rng_states])
ker_call.launch_n(1024, [rng_states, d_vec_rnd])
print (d_vec_rnd.to_host())
