#pragma once

namespace Vortex {
    enum class RendererAPI {
        None = 0, OpenGL = 1
    };

    enum class RenderProperties {
        StaticDraw = 0x88E4,
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() {return rendererAPI;}
    private:
        static RendererAPI rendererAPI;
    };
}