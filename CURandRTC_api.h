#ifndef _CURAND_RTC_API_h
#define _CURAND_RTC_API_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#pragma warning( disable: 4275 )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4530 )
#if defined CURAND_RTC_DLL_EXPORT
#define CURAND_RTC_API __declspec(dllexport)
#elif defined CURAND_RTC_DLL_IMPORT
#define CURAND_RTC_API __declspec(dllimport)
#endif
#endif

#ifndef CURAND_RTC_API
#define CURAND_RTC_API
#endif

#endif

