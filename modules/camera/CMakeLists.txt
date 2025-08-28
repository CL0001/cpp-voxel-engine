add_library(camera STATIC
        camera.cpp
)

target_include_directories(camera PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(camera PRIVATE
        glad
        glfw
        glm
)