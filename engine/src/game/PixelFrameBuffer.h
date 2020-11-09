#pragma once

#include "Pixel.h"

namespace Vortex {
    class PixelFrameBuffer {
    public:
        PixelFrameBuffer(uint32_t width, uint32_t height);

        ~PixelFrameBuffer();

        Pixel& operator[] (uint32_t index);

        uint8_t* GetUInt8Array();

    private:
        Pixel * frameBuffer;
        uint32_t width, height;
    };
}