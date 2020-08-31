#pragma once

#include "renderer/GraphicsContext.h"

class GLFWwindow;

namespace Vortex {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        void Init() override;

        void SwapBuffers() override;

    private:
        GLFWwindow* windowHandle;
    };
}