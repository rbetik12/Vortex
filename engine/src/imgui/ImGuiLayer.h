#pragma once

#include <Layer.h>
#include "events/KeyEvent.h"
#include "events/Event.h"
#include "events/MouseEvent.h"

namespace Vortex {
    class VORTEX_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer();

        void OnUpdate() override;

        void OnDetach() override;

        void OnAttach() override;

        void OnEvent(Event& event) override;

        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

        bool OnMouseMoved(MouseMovedEvent& e);

        bool OnMouseScrolled(MouseScrolledEvent& e);

        bool OnMouseButtonReleased(MouseButtonReleasedEvent &e);

        bool OnKeyPressed(KeyPressedEvent &e);

        bool OnKeyReleased(KeyReleasedEvent &e);

        bool OnKeyTyped(KeyTypedEvent &e);

        bool OnWindowResized(WindowResizeEvent &e);


    private:
        float mTime = 0.0f;
    };
}