using System;
using ThrustRTCSharp;
using CURandRTCLR;

namespace CURandRTCSharp
{
    public class DVRNG : DeviceViewable
    {
        public DVRNG() : base(Native.dvrng_create()) { }
    }
}
