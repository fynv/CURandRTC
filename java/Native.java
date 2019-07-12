package JCURandRTC;

class Native 
{
	static 
	{
		System.loadLibrary("JCURandRTC_Native"); 
	}

	public static native long dvrng_create();
}

