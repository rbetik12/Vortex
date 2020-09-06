#include "OpenGLVertexArray.h"
#include "glad/glad.h"
#include "OpenGLConverters.h"

namespace Vortex {

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &rendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(rendererID);
    }

    void OpenGLVertexArray::UnBind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
        VX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
        glBindVertexArray(rendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        for (const auto& element : vertexBuffer->GetLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    vertexBuffer->GetLayout().GetStride(),
                    (const void*) element.offset
            );
            index += 1;
        }
        vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glBindVertexArray(rendererID);
        indexBuffer->Bind();

        this->indexBuffer = indexBuffer;
    }
}
