#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Vortex {
    class VORTEX_API Log {
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {return coreLogger;}
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() {return clientLogger;}
    };
}

//Core log macros
#define VX_CORE_TRACE(...) ::Vortex::Log::getCoreLogger()->trace(__VA_ARGS__)
#define VX_CORE_INFO(...)  ::Vortex::Log::getCoreLogger()->info(__VA_ARGS__)
#define VX_CORE_WARN(...)  ::Vortex::Log::getCoreLogger()->warn(__VA_ARGS__)
#define VX_CORE_ERROR(...) ::Vortex::Log::getCoreLogger()->error(__VA_ARGS__)
#define VX_CORE_FATAL(...) ::Vortex::Log::getCoreLogger()->fatal__VA_ARGS__)

//Client log macros
#define VX_TRACE(...)      ::Vortex::Log::getClientLogger()->trace(__VA_ARGS__)
#define VX_INFO(...)       ::Vortex::Log::getClientLogger()->info(__VA_ARGS__)
#define VX_WARN(...)       ::Vortex::Log::getClientLogger()->warn(__VA_ARGS__)
#define VX_ERROR(...)      ::Vortex::Log::getClientLogger()->error(__VA_ARGS__)
#define VX_FATAL(...)      ::Vortex::Log::getClientLogger()->fatal__VA_ARGS__)
