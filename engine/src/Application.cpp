#include "Application.h"
#include <GLFW/glfw3.h>
namespace Vortex {
    Application::Application() {
        window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() {

    }

    void Application::run() {
        while (true) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            window->OnUpdate();
        }
    }
}