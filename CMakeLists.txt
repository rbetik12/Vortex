cmake_minimum_required(VERSION 3.16)
project(vortex VERSION 0.1 DESCRIPTION "Game engine project")

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
set(EXECUTABLE_OUTPUT_PATH ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME})
set(LIBRARY_OUTPUT_PATH ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME}/lib)
include_directories(engine/include)
include_directories(engine)

#Engine lib configuration
set(VORTEX_HEADERS
        engine/include/Core.h
        engine/include/Application.h
        engine/Vortex.h
        engine/include/EntryPoint.h
        )
set(VORTEX_SOURCE
        engine/src/Application.cpp
        )

add_library(vortex-engine SHARED ${VORTEX_SOURCE} ${VORTEX_HEADERS})

add_executable(vortex sandbox/src/Sandbox.cpp)
target_link_libraries(vortex vortex-engine)
