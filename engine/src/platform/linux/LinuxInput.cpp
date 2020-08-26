#include <Application.h>
#include "LinuxInput.h"

#include "GLFW/glfw3.h"

namespace Vortex {

    Input* Input::instance = new LinuxInput();

    bool LinuxInput::GetKeyDownImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS;
    }

    bool LinuxInput::GetKeyUpImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_RELEASE;
    }

    bool LinuxInput::GetMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float LinuxInput::GetMouseXImpl() {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float LinuxInput::GetMouseYImpl() {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return std::pair(xPos, yPos);
    }
}