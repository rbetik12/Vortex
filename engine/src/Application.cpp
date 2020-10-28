#include "Application.h"
#include "Log.h"
#include <iostream>
#include <glad/glad.h>
#include <game/GameField.h>

namespace Vortex {

    Application* Application::instance = nullptr;

    Application::Application() {
        VX_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        imguiLayer = new ImGuiLayer();
        PushOverlay(imguiLayer);

        vertexArray.reset(VertexArray::Create());

        float vertices[7 * 3] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices), RenderProperties::StaticDraw));


        BufferLayout layout = {
                {ShaderDataType::Float3, "position"},
                {ShaderDataType::Float4, "color"},
        };

        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {
                0, 1, 2
        };

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t), RenderProperties::StaticDraw));
        vertexArray->SetIndexBuffer(indexBuffer);

        squareVA.reset(VertexArray::Create());

        float verticesSquare[4 * 4] = {
                -1.f, -1.f, 0.0f, 0.0f,
                1.f, -1.f, 1.0f, 0.0f,
                1.f, 1.f, 1.0f, 1.0f,
                -1.f, 1.f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(verticesSquare, sizeof(verticesSquare), RenderProperties::StaticDraw));

        squareVB->SetLayout({
                                        {ShaderDataType::Float2, "position"},
                                        {ShaderDataType::Float2, "texCoord"}
                                });

        squareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(verticesSquare) / sizeof(uint32_t), RenderProperties::StaticDraw));

        squareVA->SetIndexBuffer(squareIB);

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

        std::string basicVertexShader = R"(
            #version 330 core

            layout(location = 0) in vec3 position;
            layout(location = 1) in vec2 texCoord;

            out vec2 v_TexCoord;

            void main(){
                gl_Position = vec4(position, 1.0);
                v_TexCoord = texCoord;
            }

        )";

        std::string basicFragmentShader = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;
            uniform sampler2D u_Texture;

            void main(){
                vec4 texColor = texture(u_Texture, v_TexCoord);
                color = texColor;
            }

        )";

        basicShader.reset(new Shader(basicVertexShader, basicFragmentShader));

        gameField.reset(new GameField());
        gameField->bind(0);
        basicShader->Bind();

        basicShader->setUniform1i("u_Texture", 0);

        basicShader->UnBind();
    }

    Application::~Application() {

    }

    void Application::Run() {
        while (running) {
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            basicShader->Bind();
            squareVA->Bind();
            glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            shader->Bind();
            vertexArray->Bind();
            glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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