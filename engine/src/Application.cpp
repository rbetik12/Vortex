#include "Application.h"
#include "events/ApplicationEvent.h"
#include "Log.h"
namespace Vortex {
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::run() {
        WindowResizeEvent e(1280, 720);
        VX_TRACE(e);

        while (true);
    }
}