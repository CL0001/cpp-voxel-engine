cmake_minimum_required(VERSION 3.15...4.0)

project(
    VoxelEngine
    VERSION 0.1.0
    DESCRIPTION "Voxel Engine with OpenGL"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern")
set(INTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/intern")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

add_subdirectory(${EXTERN_DIR}/glad)
add_subdirectory(${EXTERN_DIR}/glfw)
add_subdirectory(${EXTERN_DIR}/imgui)
add_subdirectory(${EXTERN_DIR}/spdlog)
add_subdirectory(${EXTERN_DIR}/glm)
add_subdirectory(${EXTERN_DIR}/stb)
add_subdirectory(${EXTERN_DIR}/json)

add_subdirectory(${INTERN_DIR})
add_subdirectory(${INTERN_DIR}/core)
add_subdirectory(${INTERN_DIR}/graphics)
add_subdirectory(${INTERN_DIR}/gui)
add_subdirectory(${INTERN_DIR}/world)

add_subdirectory(${SOURCE_DIR}/app)
