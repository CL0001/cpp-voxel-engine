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
add_subdirectory(vendor/fast_noise_lite)
add_subdirectory(vendor/stb)
add_subdirectory(vendor/nlohmann_json)

add_subdirectory(modules/core)
add_subdirectory(modules/window)
add_subdirectory(modules/shader)
add_subdirectory(modules/camera)
add_subdirectory(modules/world)
add_subdirectory(modules/renderer)
add_subdirectory(modules/texture_atlas)
add_subdirectory(modules/gui)
add_subdirectory(modules/clock)
add_subdirectory(modules/skybox)

add_subdirectory(source/app)
