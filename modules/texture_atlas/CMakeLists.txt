add_library(texture_atlas STATIC
    texture_atlas.cpp
)

target_include_directories(texture_atlas PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(texture_atlas PUBLIC
        glad
        glm
        stb
)