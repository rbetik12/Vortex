#include <glad/glad.h>
#include <vector>
#include <Log.h>
#include <platform/opengl/OpenGLErrorLog.h>
#include <iostream>
#include "Shader.h"

namespace Vortex {

    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {


// Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

// Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.

            // In this simple program, we'll just leave
            VX_CORE_ERROR("{0}", infoLog.data());
            VX_CORE_ASSERT(false, "Vertex shader compilation failed");
            return;
        }

// Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar*) fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.

            // In this simple program, we'll just leave
            VX_CORE_ERROR("{0}", infoLog.data());
            VX_CORE_ASSERT(false, "Fragment shader compilation failed");
            return;
        }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
        rendererID = glCreateProgram();
        GLuint program = rendererID;

// Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

// Link our program
        glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.

            // In this simple program, we'll just leave
            VX_CORE_ERROR("{0}", infoLog.data());
            VX_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

// Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(rendererID);
    }

    void Shader::Bind() {
        glUseProgram(rendererID);
    }

    void Shader::UnBind() {
        glUseProgram(0);
    }

    void Shader::setUniform1i(const std::string& name, int value) {
        glCall(glUniform1i(getUniformLocation(name), value));
    }

    int Shader::getUniformLocation(const std::string &name) {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        int location = glGetUniformLocation(rendererID, name.c_str());
        if (location == -1)
            std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
        m_UniformLocationCache[name] = location;
        return location;
    }
}