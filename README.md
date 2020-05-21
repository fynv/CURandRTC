# CURandRTC

This is the 2nd of the series of GPU libraries based on the 
["NVRTC + dynamic-instantiation" paradigm](https://fynv.github.io/ProgrammingGPUAcrossTheLaunguageBoundaries.html).

The library provides a simple random number generator using the XORWOW algorithm.

This project depends on the first of the series, [ThrustRTC](https://github.com/fynv/ThrustRTC).

## Installation

### Install from Source Code

You will need first get the source code of ThrustRTC and compile.

Build ThrustRTC C++ library:
```
$ git clone https://github.com/fynv/ThrustRTC.git
$ cd ThrustRTC
$ mkdir build_cpp
$ cd build_cpp
$ cmake ../cpp
$ make
$ make install
$ cd ..
```

Build ThrustRTC Python library:
```
$ mkdir build_python
$ cd build_python
$ cmake ../python
$ make
$ make install
$ cd ..
```

Build ThrustRTC Java library:
```
$ mkdir build_java
$ cd build_java
$ cmake ../java
$ make
$ make install
$ cd ..
```

Build ThrustRTC C# library:

Please use the Visual Studio project in the "CSharp" folder to build the C# library.

When you finished building the library of the language you need, you can proceed to build this CURandRTC.

First clone this repository, then copy the "install" directory from "ThrustRTC" to "CURandRTC".

Build CURandRTC C++ library:
```
$ git clone https://github.com/fynv/CURandRTC.git
$ cd CURandRTC
$ cp -r ../ThrustRTC/install .
$ mkdir build_cpp
$ cd build_cpp
$ cmake ../cpp -DBUILD_TESTS=true
$ make
$ make install
$ cd ..
```

Build CURandRTC Python library:
```
$ mkdir build_python
$ cd build_python
$ cmake ../python -DINCLUDE_TESTS=true
$ make
$ make install
$ cd ..
```

Build CURandRTC Java library:
```
$ mkdir build_java
$ cd build_java
$ cmake ../java -DBUILD_TESTS=true
$ make
$ make install
$ cd ..
```

Build CURandRTC C# library:

Please use the Visual Studio project in the "CSharp" folder to build the C# library.

You will get the library headers, binaries and examples in the "install" directory.


### Install CURandRTC for Python from Pypi

Builds for Win64/Linux64 + Python 3.7 are available from [Pypi](https://pypi.org/project/CURandRTC/)
If your environment matches, you can try:

```
$ pip3 install CURandRTC
```
You will not get the C++ library, headers as well as all the test programs using this installation method.


### GitHub Release

Zip packages are available at:

[https://github.com/fynv/CURandRTC/releases](https://github.com/fynv/CURandRTC/releases)

These libraries should be used together with the ThrustRTC libraries in the correpsonding languages.


## Examples of Usage

In C++:

```cpp
#include <stdio.h>
#include "TRTCContext.h"
#include "DVVector.h"
#include "DVRNG.h" // random number generator class

int main()
{
	DVRNG& rng = DVRNG::singlton();

	TRTC_For ker({ "rng", "vec_rnd" }, "idx",
		"    RNGState state;\n"
		"    rng.state_init(1234, idx, 0, state);\n" // initialize a state using the rng object
		"    vec_rnd[idx]=(float)state.rand01();\n" // generate random number using the rng object
	);

	DVVector d_vec_rnd("float", 1024);
	const DeviceViewable* args[] = { &rng, &d_vec_rnd };
	ker.launch_n(1024, args);

	...
}
```

In Python:
```python
import ThrustRTC as trtc
import CURandRTC as rndrtc

rng = rndrtc.DVRNG()

ker = trtc.For(['rng','vec_rnd'], 'idx',
	'''
    RNGState state;
    rng.state_init(1234, idx, 0, state);  // initialize a state using the rng object
   	vec_rnd[idx]=(float)state.rand01(); // generate random number using the rng object
	''')

d_vec_rnd = trtc.device_vector('float', 1024)
ker.launch_n(1024, [rng, d_vec_rnd])
...
```

In C#:
```cs
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
    rng.state_init(1234, idx, 0, state);  // initialize a state using the rng object
    vec_rnd[idx]=(float)state.rand01(); // generate random number using the rng object "); 

            DVVector d_vec_rnd = new DVVector("float", 1024);
            DeviceViewable[] kargs = new DeviceViewable[] { rng, d_vec_rnd };
            ker.launch_n(1024, kargs);
            ...

        }
        ...
    }
}

```

In JAVA:
```java
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
		"    rng.state_init(1234, idx, 0, state); // initialize a state using the rng object\n",
		"    vec_rnd[idx]=(float)state.rand01(); // generate random number using the rng object \n"));
		DVVector d_vec_rnd = new DVVector("float", 1024);
		DeviceViewable[] kargs = new DeviceViewable[] { rng, d_vec_rnd };
		ker.launch_n(1024, kargs);
		...
	}
}

```

## License 

I've decided to license this project under ['"Anti 996" License'](https://github.com/996icu/996.ICU/blob/master/LICENSE)

Basically, you can use the code any way you like unless you are working for a 996 company.

[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)

