#pragma once

#include <memory>
#include "Core.h"
#include "events/Event.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include <events/ApplicationEvent.h>
#include <imgui/ImGuiLayer.h>

namespace Vortex {
    class Application {
    public:
        Application();

        virtual ~Application();

        void run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);

        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *instance; }

        inline Window& GetWindow() { return *window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> window;
        ImGuiLayer* imguiLayer;
        bool running = true;
        LayerStack layerStack;

        unsigned int vertexBuffer, indexBuffer, vertexArray;

        static Application* instance;
    };

    Application* createApplication();
}