#include <cstddef>
#include "PixelFrameBuffer.h"

namespace Vortex {

    PixelFrameBuffer::PixelFrameBuffer(uint32_t width, uint32_t height) : width(width), height(height) {
        frameBuffer = new Pixel[width * height];
    }

    PixelFrameBuffer::~PixelFrameBuffer() {
        delete[] frameBuffer;
    }

    Pixel& PixelFrameBuffer::operator[](const uint32_t index) {
        return frameBuffer[index];
    }

    uint8_t* PixelFrameBuffer::GetUInt8Array() {
        auto* pixelArray = new uint8_t[width * height * 4];
        size_t pixelArrayIndex = 0;
        for (int i = 0; i < width * height; i++) {
            pixelArray[pixelArrayIndex++] = frameBuffer[i].GetColor().r;
            pixelArray[pixelArrayIndex++] = frameBuffer[i].GetColor().g;
            pixelArray[pixelArrayIndex++] = frameBuffer[i].GetColor().b;
            pixelArray[pixelArrayIndex++] = frameBuffer[i].GetColor().a;
        }
        return pixelArray;
    }
}
