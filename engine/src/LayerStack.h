#pragma once

#include "Layer.h"

namespace Vortex {
    class LayerStack {
    public:
        LayerStack();

        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() {return layers.begin();}
        std::vector<Layer*>::iterator end() { return layers.end();}
    private:
        std::vector<Layer*> layers;
        unsigned int layerInsertIndex = 0;
    };
}