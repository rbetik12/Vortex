cmake_minimum_required(VERSION 3.16)
project(engine)

set(CMAKE_CXX_STANDARD 20)

#Preprocessor configuration
if (UNIX)
    add_definitions(-DVX_PLATFORM_LINUX)
endif()
add_definitions(-DVX_ENABLE_ASSERTS)

#Include directories
include_directories(src)
include_directories(vendor/spdlog/include)
include_directories(vendor/glfw/include)
include_directories(vendor/glad/include)
include_directories(vendor/imgui)
include_directories(vendor/glm)

#Engine lib configuration
set(VORTEX_SOURCE
        src/Core.h
        src/Application.h
        Vortex.h
        src/EntryPoint.h
        src/Log.h
        src/events/Event.h src/events/KeyEvent.h src/events/MouseEvent.h src/events/ApplicationEvent.h src/Window.h src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h
        src/Application.cpp
        src/Log.cpp
        src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h src/Layer.cpp src/Layer.h src/LayerStack.cpp src/LayerStack.h src/imgui/ImGuiLayer.h src/imgui/ImGuiLayer.cpp src/Input.h src/platform/linux/LinuxInput.cpp src/platform/linux/LinuxInput.h src/KeyCodes.h src/MouseButtonCodes.h src/imgui/ImGuiBuild.cpp src/renderer/GraphicsContext.h src/platform/opengl/OpenGLContext.cpp src/platform/opengl/OpenGLContext.h src/renderer/Shader.h src/renderer/Shader.cpp src/renderer/Buffer.h src/renderer/Buffer.cpp src/platform/opengl/OpenGLBuffer.cpp src/platform/opengl/OpenGLBuffer.h src/renderer/Renderer.h src/renderer/Renderer.cpp src/renderer/VertexArray.h src/renderer/VertexArray.cpp src/platform/opengl/OpenGLVertexArray.cpp src/platform/opengl/OpenGLVertexArray.h src/platform/opengl/OpenGLConverters.h src/renderer/textures/Texture.h src/game/GameField.h src/platform/opengl/OpenGLErrorLog.h src/game/GameField.cpp src/platform/opengl/OpenGLErrorLog.cpp)

add_library(engine STATIC ${VORTEX_SOURCE} ${VORTEX_HEADERS})

target_link_libraries(engine glad imgui glfw)