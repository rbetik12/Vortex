#pragma once

#include "renderer/textures/Texture.h"
#include "Pixel.h"
#include "PixelFrameBuffer.h"

namespace Vortex {
    class GameField : public Texture {
    private:
        PixelFrameBuffer frameBuffer;
        uint32_t rendererId;
        uint32_t width, height;
    public:
        GameField();

        ~GameField();

        virtual void bind(unsigned int slot = 0) const override;

        virtual void unBind() const override;

        virtual inline int getWidth() const override {return width;}

        virtual inline int getHeight() const override { return height; }

        void Update();
    };
}