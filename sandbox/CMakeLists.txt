cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(CMAKE_CXX_STANDARD 20)

#Initial config
set(CONFIGURATION debug)
set(PLATFORM linux)

#Preprocessor configuration
if (${PLATFORM} STREQUAL "linux")
    add_definitions(-DVX_PLATFORM_LINUX)
endif()

set(EXECUTABLE_OUTPUT_PATH ../bin/${CONFIGURATION}-${PLATFORM}/${CMAKE_PROJECT_NAME})

include_directories(../engine)
include_directories(../engine/include)
include_directories(../engine/src)
include_directories(../engine/src/imgui)
include_directories(../engine/vendor/spdlog/include)
include_directories(../engine/vendor/glm)

set(SANDBOX_SOURCES
        src/Sandbox.cpp
        )

add_executable(${CMAKE_PROJECT_NAME} ${SANDBOX_SOURCES})


add_dependencies(${CMAKE_PROJECT_NAME} engine)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE engine glfw GL)






