add_library(world STATIC
        chunk.cpp
        world.cpp
)

target_include_directories(world PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(world PUBLIC
        glad
        glm
        fastnoiselite
        shader
)