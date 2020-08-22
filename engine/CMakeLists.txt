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

#Compiler configuration
set(CFLAGS -m64 -fvisibility=hidden)
set(LIBRARY_OUTPUT_PATH  ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME}/lib)

#Include directories
include_directories(src)
include_directories(vendor/spdlog/include)
include_directories(vendor/glfw/include)

#Engine lib configuration
set(VORTEX_HEADERS
        src/Core.h
        src/Application.h
        Vortex.h
        src/EntryPoint.h
        src/Log.h
        src/events/Event.h src/events/KeyEvent.h src/events/MouseEvent.h src/events/ApplicationEvent.h src/Window.h src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h)
set(VORTEX_SOURCE
        src/Application.cpp
        src/Log.cpp
        src/platform/linux/LinuxWindow.cpp src/platform/linux/LinuxWindow.h)

add_library(engine SHARED ${VORTEX_SOURCE} ${VORTEX_HEADERS})