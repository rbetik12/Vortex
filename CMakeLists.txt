cmake_minimum_required(VERSION 3.16)
project(vortex)

add_subdirectory(engine/vendor/imgui)
add_subdirectory(engine/vendor/glfw)
add_subdirectory(engine/vendor/glad)

add_subdirectory(engine)
add_subdirectory(sandbox)