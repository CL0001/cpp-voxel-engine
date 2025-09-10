add_library(gui STATIC
        gui_manager.cpp
        controls_panel.cpp
        stats_panel.cpp
)

target_include_directories(gui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gui PRIVATE
        glfw
        imgui
)