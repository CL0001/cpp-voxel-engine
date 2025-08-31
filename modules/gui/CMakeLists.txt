add_library(gui STATIC
        gui.cpp
)

target_include_directories(gui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gui PUBLIC
        glfw
        imgui
)