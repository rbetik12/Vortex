#pragma once
#include <cstdint>

namespace Vortex {
    struct Color32 {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color32() {
            r = 255;
            g = 255;
            b = 255;
            a = 255;
        }
    };
}