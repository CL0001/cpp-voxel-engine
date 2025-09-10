add_library(engine-graphics STATIC
        camera/camera.cpp camera/camera.h
        renderer/renderer.cpp renderer/renderer.h
        shader/shader.cpp shader/shader.h
        skybox/skybox.cpp skybox/skybox.h
        texture_atlas/texture_atlas.cpp texture_atlas/texture_atlas.h
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
