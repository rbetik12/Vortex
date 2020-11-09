#include "Pixel.h"

namespace Vortex {

    Pixel::Pixel(): color(Color32()), type(Sand) {

    }

    Pixel::Pixel(Color32 color, PixelType type): color(color), type(type) {

    }

    Pixel::~Pixel() = default;
}
