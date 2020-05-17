#include "Log.h"

namespace Vortex {
    std::shared_ptr<spdlog::logger> Log::clientLogger;
    std::shared_ptr<spdlog::logger> Log::coreLogger;

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("VORTEX");
        coreLogger->set_level(spdlog::level::trace);
        clientLogger = spdlog::stderr_color_mt("APP");
        clientLogger->set_level(spdlog::level::trace);
    }
}