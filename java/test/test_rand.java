import java.util.*;
import JThrustRTC.*;
import JCURandRTC.*;

public class test_rand 
{
	public static void main(String[] args) 
	{
        DVRNG rng = new DVRNG();
        For ker = new For(new String[] { "rng", "vec_rnd" }, "idx",
        String.join("",
		"    RNGState state;\n",
		"    rng.state_init(1234, idx, 0, state);\n",
		"    for (int i=0; i<32; i++)\n",
		"        vec_rnd[i+idx*32]=(float)rng.rand01(state);\n"));
		DVVector d_vec_rnd = new DVVector("float", 1024);
		DeviceViewable[] kargs = new DeviceViewable[] { rng, d_vec_rnd };
		ker.launch_n(32, kargs);
		System.out.println(Arrays.toString((float[])d_vec_rnd.to_host()));		
	}
}
