#pragma once

#include <Core.h>
#include <events/Event.h>

namespace Vortex {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");

        virtual ~Layer() {}

        virtual void OnAttach() {}

        virtual void OnDetach() {}

        virtual void OnUpdate() {}

        virtual void OnImGuiRender() {}

        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return debugName; }

    protected:
        std::string debugName;
    };
}

