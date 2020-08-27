#include <vendor/imgui/imgui.h>
#include "Vortex.h"

class ExampleLayer: public Vortex::Layer {
public:
    ExampleLayer():Layer("Example") {}

    void OnUpdate() override {
        if (Vortex::Input::GetKeyDown(VX_KEY_TAB)) {
            VX_TRACE("Tab is polled");
        }
    }

    void OnEvent(Vortex::Event& event) override {
    }

    void OnImGuiRender() override {
        ImGui::Begin("Test");

        ImGui::Text("test");

        ImGui::End();
    }
};

class Sandbox : public Vortex::Application {
    public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() {

    }
};

Vortex::Application* Vortex::createApplication() {
    return new Sandbox();
}

