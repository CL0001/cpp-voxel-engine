add_library(engine-world STATIC
        chunk.cpp chunk.h
        chunk_manager.cpp chunk_manager.h
)

target_include_directories(engine-world PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-world PUBLIC
        glfw
        imgui
        glm
        engine-core
        engine-graphics
)

target_compile_definitions(engine-world PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")
