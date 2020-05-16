#pragma once
#include "Core.h"
namespace Vortex {
    class VORTEX_API Application {
    public:
        Application();

        virtual ~Application();

        void run();
    };

    Application* createApplication();
}