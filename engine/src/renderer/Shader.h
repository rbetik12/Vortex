#pragma once

#include <string>

namespace Vortex {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentShader);
        ~Shader();

        void Bind();
        void UnBind();

        void setUniform1i(const std::string& name, int value);

    private:
        uint32_t rendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        int getUniformLocation(const std::string& name);
    };
}