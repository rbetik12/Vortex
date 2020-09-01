#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core.h>
#include "OpenGLContext.h"
namespace Vortex {

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        VX_CORE_ASSERT(status, "Failed to initialize Glad!")

        VX_CORE_INFO("OpenGL Info:");
        VX_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        VX_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        VX_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(windowHandle);
    }

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): windowHandle(windowHandle) {
        VX_CORE_ASSERT(windowHandle, "Window handle is null!")
    }
}