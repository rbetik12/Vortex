#include <Core.h>
#include <platform/opengl/OpenGLBuffer.h>
#include "Buffer.h"

namespace Vortex {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size, RenderProperties drawMode) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: VX_CORE_ASSERT(false, "RendererAPI::None currently is not supported!")
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size, drawMode);
            default: VX_CORE_ASSERT(false, "Unknown rendering API!")
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count, RenderProperties drawMode) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: VX_CORE_ASSERT(false, "RendererAPI::None currently is not supported!")
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, count, drawMode);
            default: VX_CORE_ASSERT(false, "Unknown rendering API!")
                return nullptr;
        }
    }
}
