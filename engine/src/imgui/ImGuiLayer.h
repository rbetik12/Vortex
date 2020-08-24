#pragma once

#include <Layer.h>

namespace Vortex {
    class VORTEX_API ImGuiLayer: public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;

        void OnDetach() override;

        void OnAttach() override;

        void OnEvent(Event& event) override;
    private:
        float mTime = 0.0f;
    };
}