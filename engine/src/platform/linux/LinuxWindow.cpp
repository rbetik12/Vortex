#include <Log.h>
#include "LinuxWindow.h"

namespace Vortex {
    static bool glfwInitialized = false;

    Window* Window::Create(const WindowProps& props) {
        return new LinuxWindow(props);
    }


    LinuxWindow::LinuxWindow(const WindowProps& props) {
        Init(props);
    }

    LinuxWindow::~LinuxWindow() {
        Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props) {
        data.width = props.width;
        data.height = props.height;
        data.title = props.title;

        VX_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!glfwInitialized) {
            int success = glfwInit();

            VX_CORE_ASSERT(success, "Could not initialize GLFW");

            glfwInitialized = true;
        }

        window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &data);
        SetVSync(true);
    }

    void LinuxWindow::Shutdown() {
        glfwDestroyWindow(window);
    }

    void LinuxWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void LinuxWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }

        data.vSync = enabled;
    }

    bool LinuxWindow::IsVSync() const {
        return data.vSync;
    }


}
