add_library(renderer STATIC
        renderer.cpp
)

target_include_directories(renderer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(renderer PUBLIC
        glad
        engine
        shader
        camera
        texture_atlas
        gui
        clock
        skybox
)

target_compile_definitions(renderer PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")
