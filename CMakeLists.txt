cmake_minimum_required(VERSION 3.15...4.0)

project(
    VoxelEngine
    VERSION 0.1.0
    DESCRIPTION "Voxel Engine with OpenGL"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/fastnoiselite)

add_subdirectory(modules/core)
add_subdirectory(modules/window)
add_subdirectory(modules/shader)
add_subdirectory(modules/camera)

add_subdirectory(source/app)
