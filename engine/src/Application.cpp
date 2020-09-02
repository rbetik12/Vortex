#include "Application.h"
#include "Log.h"
#include <iostream>
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Vortex {

    Application* Application::instance = nullptr;

    Application::Application() {
        VX_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        imguiLayer = new ImGuiLayer();
        PushOverlay(imguiLayer);

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        unsigned int indices[3] = {
                0, 1, 2
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 position;

            out vec3 vPosition;

            void main(){
                vPosition = position;
                gl_Position = vec4(position, 1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;

            void main(){
                color = vec4(vPosition * 0.5 + 0.5, 1.0);
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
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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