#include "Vortex.h"

class ExampleLayer: public Vortex::Layer {
public:
    ExampleLayer():Layer("Example") {}

    void OnUpdate() override {
        VX_INFO("ExampleLayer::Update");
    }

    void OnEvent(Vortex::Event& event) override {
        VX_TRACE("{0}", event);
    }
};

class Sandbox : public Vortex::Application {
    public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new Vortex::ImGuiLayer());
    }
    ~Sandbox() {

    }
};

Vortex::Application* Vortex::createApplication() {
    return new Sandbox();
}

