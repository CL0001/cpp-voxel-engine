add_library(clock STATIC
        clock.cpp
)

target_include_directories(clock PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(clock PRIVATE
        glfw
)