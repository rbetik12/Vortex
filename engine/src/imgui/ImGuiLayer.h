#pragma once

#include <Layer.h>
#include "events/KeyEvent.h"
#include "events/Event.h"
#include "events/MouseEvent.h"

namespace Vortex {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer();

        virtual void OnDetach() override;

        virtual void OnAttach() override;

        void OnImGuiRender() override;

        void Begin();

        void End();

    private:
        float mTime = 0.0f;
    };
}