#pragma once

#ifdef VX_PLATFORM_LINUX

extern Vortex::Application* Vortex::createApplication();

int main() {
    Vortex::Log::init();
    VX_CORE_WARN("Initialized log");
    VX_INFO("Hello!");
    auto app = Vortex::createApplication();
    app->run();
    delete app;
    return 0;
}

#endif