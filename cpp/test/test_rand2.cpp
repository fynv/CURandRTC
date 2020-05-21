#include <stdio.h>
#include "TRTCContext.h"
#include "DVVector.h"
#include "DVRNG.h"

int main()
{
	DVRNG& rng = DVRNG::singlton();

	TRTC_For ker_init({ "rng", "vec_states" }, "idx",
		"    rng.state_init(1234, idx, 0, vec_states[idx]);\n"
	);

	TRTC_For ker_call({ "vec_states", "vec_rnd" }, "idx",
		"    vec_rnd[idx]=(float)vec_states[idx].rand01();\n"
	);

	DVVector d_vec_states("RNGState", 1024);
	DVVector d_vec_rnd("float", 1024);
	{
		const DeviceViewable* args[] = { &rng, &d_vec_states };
		ker_init.launch_n(1024, args);
	}
	{
		const DeviceViewable* args[] = { &d_vec_states, &d_vec_rnd };
		ker_call.launch_n(1024, args);
	}

	float h_vec_rnd[1024];
	d_vec_rnd.to_host(h_vec_rnd);

	for (int i = 0; i < 1024; i++)
		printf("%f ", h_vec_rnd[i]);

	printf("\n");

	return 0;
}
