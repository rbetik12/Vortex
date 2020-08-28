#include <Log.h>
#include <events/ApplicationEvent.h>
#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <glad/glad.h>
#include "LinuxWindow.h"

namespace Vortex {
    static bool glfwInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        VX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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

        window = glfwCreateWindow((int) props.width, (int) props.height, data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        VX_CORE_ASSERT(status, "Failed to initialize Glad!")
        glfwSetWindowUserPointer(window, &data);
        SetVSync(true);

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseScrolledEvent event(xOffset, yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseMovedEvent event(xPos, yPos);
            data.eventCallback(event);
        });
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
        } else {
            glfwSwapInterval(0);
        }

        data.vSync = enabled;
    }

    bool LinuxWindow::IsVSync() const {
        return data.vSync;
    }


}
