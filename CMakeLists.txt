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

set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
set(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

add_subdirectory(${VENDOR_DIR}/glad)
add_subdirectory(${VENDOR_DIR}/glfw)
add_subdirectory(${VENDOR_DIR}/imgui)
add_subdirectory(${VENDOR_DIR}/spdlog)
add_subdirectory(${VENDOR_DIR}/glm)
add_subdirectory(${VENDOR_DIR}/stb)
add_subdirectory(${VENDOR_DIR}/nlohmann_json)

add_subdirectory(${MODULES_DIR}/camera)
add_subdirectory(${MODULES_DIR}/clock)
add_subdirectory(${MODULES_DIR}/gui)
add_subdirectory(${MODULES_DIR}/renderer)
add_subdirectory(${MODULES_DIR}/shader)
add_subdirectory(${MODULES_DIR}/skybox)
add_subdirectory(${MODULES_DIR}/texture_atlas)
add_subdirectory(${MODULES_DIR}/window)

add_subdirectory(${SOURCE_DIR}/application)
add_subdirectory(${SOURCE_DIR}/engine)
