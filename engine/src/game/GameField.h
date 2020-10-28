#pragma once

#include "renderer/textures/Texture.h"

namespace Vortex {
    class GameField : public Texture {
    private:
        unsigned char* frameBuffer;
        uint32_t rendererId;
        uint32_t width, height, BPP;
    public:
        GameField();

        ~GameField();

        virtual void bind(unsigned int slot = 0) const override;

        virtual void unBind() const override;

        virtual inline int getWidth() const override {return width;}

        virtual inline int getHeight() const override { return height; }
    };
}