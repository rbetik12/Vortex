cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(CMAKE_CXX_STANDARD 20)

#Initial config
set(CONFIGURATION debug)
set(PLATFORM linux)

#Preprocessor configuration
if (${PLATFORM} STREQUAL "linux")
    add_definitions(-DVX_PLATFORM_LINUX)
    add_definitions(-DVX_BUILD_SO)
endif()

set(EXECUTABLE_OUTPUT_PATH ../../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME})

include_directories(../engine)
include_directories(../engine/include)
include_directories(../engine/src)
include_directories(../engine/vendor/spdlog/include)

set(SANDBOX_SOURCES
        src/Sandbox.cpp
        )

get_filename_component(LIB_ABS_ENGINE_PATH ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME}/lib ABSOLUTE)
find_library(LIB_ENGINE engine PATHS "${LIB_ABS_ENGINE_PATH}")

add_executable(${CMAKE_PROJECT_NAME} ${SANDBOX_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_ENGINE})



