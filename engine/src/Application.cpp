#include "Application.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Input.h"

namespace Vortex {

    Application* Application::instance = nullptr;

    Application::Application() {
        VX_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {

    }

    void Application::run() {
        while (running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer: layerStack) {
                layer->OnUpdate();
            }

            auto [x, y] = Input::GetMousePosition();
            VX_CORE_TRACE("{0}, {1}", x, y);

            window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.handled) {
                break;
            }
        }

        VX_CORE_TRACE("{0}", e);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        layerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}