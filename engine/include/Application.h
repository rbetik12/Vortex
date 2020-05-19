#pragma once
#include "Core.h"
#include "events/Event.h"
namespace Vortex {
    class VORTEX_API Application {
    public:
        Application();

        virtual ~Application();

        void run();
    };

    Application* createApplication();
}