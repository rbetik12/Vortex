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
set(LIBRARY_OUTPUT_PATH  ../../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME}/lib)

#Include directories
include_directories(include)
include_directories(src)
include_directories(vendor/spdlog/include)

#Engine lib configuration
set(VORTEX_HEADERS
        include/Core.h
        include/Application.h
        Vortex.h
        include/EntryPoint.h
        include/Log.h
        src/events/Event.h src/events/KeyEvent.h src/events/MouseEvent.h src/events/ApplicationEvent.h)
set(VORTEX_SOURCE
        src/Application.cpp
        src/Log.cpp
        )

add_library(engine SHARED ${VORTEX_SOURCE} ${VORTEX_HEADERS})