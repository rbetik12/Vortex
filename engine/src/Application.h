#pragma once

#include <memory>
#include "Core.h"
#include "events/Event.h"
#include "Window.h"

namespace Vortex {
    class VORTEX_API Application {
    public:
        Application();

        virtual ~Application();

        void run();

    private:
        std::unique_ptr<Window> window;
        bool running = true;
    };

    Application* createApplication();
}