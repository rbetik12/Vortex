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

#define BIT(x) (1 << x)