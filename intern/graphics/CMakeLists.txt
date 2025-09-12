add_library(engine-graphics STATIC
        camera/camera.cpp camera/camera.hpp
        renderer/renderer.cpp renderer/renderer.hpp
        shader/shader.cpp shader/shader.hpp
        skybox/skybox.cpp skybox/skybox.hpp
        texture_atlas/texture_atlas.cpp texture_atlas/texture_atlas.hpp
)

target_include_directories(engine-graphics PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-graphics PUBLIC
        glfw
        glad
        glm
        stb
        json
        spdlog
)

target_compile_definitions(engine-graphics PUBLIC
        ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/"
)
