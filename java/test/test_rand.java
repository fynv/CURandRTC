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
		"    vec_rnd[idx]=(float)state.rand01();\n"));
		DVVector d_vec_rnd = new DVVector("float", 1024);
		DeviceViewable[] kargs = new DeviceViewable[] { rng, d_vec_rnd };
		ker.launch_n(1024, kargs);
		System.out.println(Arrays.toString((float[])d_vec_rnd.to_host()));		
	}
}
