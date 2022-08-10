#pragma once

#ifdef LS_PLATFORM_WINDOWS
	#ifdef LS_BUILD_DLL
		#define LOSTSOULS_API __declspec(dllexport)
	#else
		#define LOSTSOULS_API __declspec(dllimport)
	#endif
#else
	#error LostSouls currently only supports windows...
#endif

#define BIT(x) (1 << x)