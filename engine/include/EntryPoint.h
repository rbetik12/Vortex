#pragma once

#ifdef VX_PLATFORM_LINUX

extern Vortex::Application * Vortex::createApplication();

int main(int argc, char** argv) {
    auto app = Vortex::createApplication();
    app->run();
    delete app;
    return 0;
}

#endif