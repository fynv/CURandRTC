#include <stdio.h>
#include "TRTCContext.h"
#include "DVVector.h"
#include "DVRNG.h"

int main()
{
	DVRNG& rng = DVRNG::singlton();

	TRTC_For ker({ "rng", "vec_rnd" }, "idx",
		"    RNGState state;\n"
		"    rng.state_init(1234, idx, 0, state);\n"
		"    for (int i=0; i<32; i++)\n"
		"        vec_rnd[i+idx*32]=(float)rng.rand01(state);\n"
	);

	DVVector d_vec_rnd("float", 1024);
	const DeviceViewable* args[] = { &rng, &d_vec_rnd };
	ker.launch_n(32, args);

	float h_vec_rnd[1024];
	d_vec_rnd.to_host(h_vec_rnd);

	for (int i = 0; i < 1024; i++)
		printf("%f ", h_vec_rnd[i]);

	printf("\n");

	return 0;
}
