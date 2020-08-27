#pragma once

#ifdef VX_PLATFORM_LINUX

#include <csignal>

#ifdef VX_BUILD_SO
#define VORTEX_API
#else
#define VORTEX_API __attribute__ ((dllimport))
#endif
#else
#error Vortex only support Linux!
#endif

#ifdef VX_ENABLE_ASSERTS
#define VX_ASSERT(x, ...) { if(!(x)) { VX_ERROR("Assertion Failed: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#define VX_CORE_ASSERT(x, ...) { if(!(x)) { VX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); raise(SIGTRAP); } }
#else
#define VX_ASSERT(x, ...)
#define VX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)