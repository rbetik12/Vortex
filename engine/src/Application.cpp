#include "Application.h"
#include "Log.h"
#include <iostream>
#include <glad/glad.h>

namespace Vortex {

    Application* Application::instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        VX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application::Application() {
        VX_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        imguiLayer = new ImGuiLayer();
        PushOverlay(imguiLayer);

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        float vertices[7 * 3] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f
        };

        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices), RenderProperties::StaticDraw));
        vertexBuffer->Bind();

        {
            BufferLayout layout = {
                    {ShaderDataType::Float3, "position"},
                    {ShaderDataType::Float4, "color"},
            };

            vertexBuffer->SetLayout(layout);
        }

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

        uint32_t indices[3] = {
                0, 1, 2
        };

        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t), RenderProperties::StaticDraw));
        indexBuffer->Bind();

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec4 color;

            out vec3 vPosition;
            out vec4 vColor;

            void main(){
                vPosition = position;
                vColor = color;
                gl_Position = vec4(position, 1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;
            in vec4 vColor;

            void main(){
                color = vec4(vPosition * 0.5 + 0.5, 1.0);
                color = vColor;
            }

        )";

        shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() {

    }

    void Application::run() {
        while (running) {
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);


            shader->Bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer: layerStack) {
                layer->OnUpdate();
            }

            imguiLayer->Begin();
            for (Layer* layer: layerStack) {
                layer->OnImGuiRender();
            }
            imguiLayer->End();

            window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer) {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        layerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}