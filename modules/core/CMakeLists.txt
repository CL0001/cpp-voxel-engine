add_library(core
        engine.cpp
)

target_include_directories(core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core PUBLIC
        glfw
        imgui
        glm
        window
        world
        shader
        camera
        renderer
)

if (WIN32)
    target_link_libraries(core PUBLIC opengl32)
elseif (APPLE)
    target_link_libraries(core PUBLIC "-framework OpenGL")
else()
    target_link_libraries(core PUBLIC GL)
endif()

target_compile_definitions(core PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")