#pragma once

#include <memory>
#include "Core.h"
#include "events/Event.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include <events/ApplicationEvent.h>

namespace Vortex {
    class VORTEX_API Application {
    public:
        Application();

        virtual ~Application();

        void run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> window;
        bool running = true;
        LayerStack layerStack;
    };

    Application* createApplication();
}