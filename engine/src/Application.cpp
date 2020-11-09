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
            gameField->Update();
            squareVA->Bind();
            glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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