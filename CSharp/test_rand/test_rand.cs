using System;
using ThrustRTCSharp;
using CURandRTCSharp;

namespace test_rand
{
    class test_rand
    {
        static void Main(string[] args)
        {
            DVRNG rng = new DVRNG();
            For ker = new For(new string[] { "rng", "vec_rnd" }, "idx",
@"
    RNGState state;
    rng.state_init(1234, idx, 0, state);
    vec_rnd[idx]=(float)state.rand01();");

            DVVector d_vec_rnd = new DVVector("float", 1024);
            DeviceViewable[] kargs = new DeviceViewable[] { rng, d_vec_rnd };
            ker.launch_n(1024, kargs);
            print_array((float[])d_vec_rnd.to_host());

        }

        static void print_array<T>(T[] arr)
        {
            foreach (var item in arr)
            {
                Console.Write(item.ToString());
                Console.Write(" ");
            }
            Console.WriteLine("");
        }
    }
}
