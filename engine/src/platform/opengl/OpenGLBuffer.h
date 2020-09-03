#pragma once

#include <renderer/Buffer.h>
#include "glad/glad.h"

namespace Vortex {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size, RenderProperties drawMode);

        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;

        virtual void UnBind() const override;

    private:
        uint32_t rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count, RenderProperties drawMode);

        virtual ~OpenGLIndexBuffer() override;

        void Bind() const override;

        void UnBind() const override;

        uint32_t GetCount() const override;

    private:
        uint32_t rendererID;
        uint32_t count;
    };
}