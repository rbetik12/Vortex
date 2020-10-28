#pragma once

#include <cstdint>

namespace Vortex {
    class Texture {
    public:
        virtual void bind(unsigned int slot = 0) const = 0;

        virtual void unBind() const = 0;

        virtual inline int getWidth() const = 0;

        virtual inline int getHeight() const = 0;
    };
}