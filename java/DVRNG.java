package JCURandRTC;

import JThrustRTC.DeviceViewable;

public class DVRNG extends DeviceViewable
{
	public DVRNG()
	{
		super(Native.dvrng_create());
	}
}

