#pragma once

#include <string>

namespace Vortex {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentShader);
        ~Shader();

        void Bind();
        void UnBind();

    private:
        uint32_t rendererID;
    };
}