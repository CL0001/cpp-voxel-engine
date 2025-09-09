set(LIB_NAME engine)

add_library(${LIB_NAME} STATIC
        chunk.cpp
        engine.cpp
        world.cpp
)

target_include_directories(${LIB_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME} PUBLIC
        glfw
        imgui
        glm
        window
        shader
        camera
        renderer
        gui
        clock
)

if (WIN32)
    target_link_libraries(${LIB_NAME} PUBLIC opengl32)
elseif (APPLE)
    target_link_libraries(${LIB_NAME} PUBLIC "-framework OpenGL")
else()
    target_link_libraries(${LIB_NAME} PUBLIC GL)
endif()

target_compile_definitions(${LIB_NAME} PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")
