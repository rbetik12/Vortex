#include <platform/opengl/OpenGLVertexArray.h>
#include "VertexArray.h"

namespace Vortex {

    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: VX_CORE_ASSERT(false, "RendererAPI::None currently is not supported!")
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
            default: VX_CORE_ASSERT(false, "Unknown rendering API!")
                return nullptr;
        }
    }
}
