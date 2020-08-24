cmake_minimum_required(VERSION 3.16)
project(engine)

set(CMAKE_CXX_STANDARD 20)
#Initial config
set(CONFIGURATION debug)
set(PLATFORM linux)

#Preprocessor configuration
if (${PLATFORM} STREQUAL "linux")
    add_definitions(-DVX_PLATFORM_LINUX)
    add_definitions(-DVX_BUILD_SO)
endif()
add_definitions(-DVX_ENABLE_ASSERTS)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

#Compiler configuration
set(CFLAGS -m64 -fvisibility=hidden)
set(LIBRARY_OUTPUT_PATH  ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME}/lib)

#Include directories
include_directories(src)
include_directories(vendor/spdlog/include)
include_directories(vendor/glfw/include)
include_directories(vendor/glad/include)
include_directories(vendor/imgui)

#Engine lib configuration
set(VORTEX_HEADERS
        src/Core.h
        src/Application.h
        Vortex.h
        src/EntryPoint.h
        src/Log.h
        src/platform/opengl/ImGuiOpenGLRenderer.cpp
        src/platform/opengl/ImGuiOpenGLRenderer.h
        src/events/Event.h src/events/KeyEvent.h src/events/MouseEvent.h src/events/ApplicationEvent.h src/Window.h src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h)
set(VORTEX_SOURCE
        src/Application.cpp
        src/Log.cpp
        src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h src/Layer.cpp src/Layer.h src/LayerStack.cpp src/LayerStack.h src/imgui/ImGuiLayer.h src/imgui/ImGuiLayer.cpp)

add_library(engine SHARED ${VORTEX_SOURCE} ${VORTEX_HEADERS})

target_link_libraries(engine glad imgui)