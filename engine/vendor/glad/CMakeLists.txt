cmake_minimum_required(VERSION 3.16)
project(glad)

set(CMAKE_CXX_STANDARD 20)

set(CFLAGS -m64 -fvisibility=hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

set(GLAD_SOURCE
        include/glad/glad.h
        include/KHR/khrplatform.h
        src/glad.c
        )

include_directories(include)

add_library(glad STATIC ${GLAD_SOURCE})