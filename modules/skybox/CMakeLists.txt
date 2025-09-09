add_library(skybox STATIC
        skybox.cpp
)

target_include_directories(skybox PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(skybox PRIVATE
        glad
        stb
        shader
        camera
)
