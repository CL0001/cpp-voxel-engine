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

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
    PRIVATE
    source/main.cpp
    source/shader.cpp
    source/engine.cpp
    source/cube.cpp

    PUBLIC
    include/shader.h
    include/engine.h
    include/cube.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw imgui spdlog)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE GL)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")