import ThrustRTC as trtc
import CURandRTC as rndrtc

rng = rndrtc.DVRNG()

ker = trtc.For(['rng','vec_rnd'], 'idx',
	'''
    RNGState state;
    rng.state_init(1234, idx, 0, state);
    vec_rnd[idx]=(float)state.rand01();
	''')

d_vec_rnd = trtc.device_vector('float', 1024)
ker.launch_n(1024, [rng, d_vec_rnd])
print (d_vec_rnd.to_host())
