#pragma once


#include <renderer/VertexArray.h>

namespace Vortex {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray() override;

        void Bind() const override;

        void UnBind() const override;

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; }

        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    private:
        uint32_t rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}