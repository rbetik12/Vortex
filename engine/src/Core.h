#pragma once

#ifdef VX_PLATFORM_LINUX
    #ifdef VX_BUILD_SO
        #define VORTEX_API __attribute__ ((dllexport))
    #else
        #define VORTEX_API __attribute__ ((dllimport))
    #endif
#else
    #error Vortex only support Linux!
#endif

#ifdef VX_ENABLE_ASSERTS
    #define VX_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); raise(SIGTRAP); } }
	#define VX_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#else
#define VX_ASSERT(x, ...)
#define VX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)