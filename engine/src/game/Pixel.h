#pragma once
#include <cstdint>
#include <renderer/Color32.h>
#include "PixelType.h"

namespace Vortex {
    class Pixel {
    public:
        Pixel();
        Pixel(Color32 color, PixelType type);

        ~Pixel();

        inline Color32& GetColor() {return color;}

    private:
        Color32 color;
        PixelType type;
    };
}