add_library(engine-gui STATIC
        gui_manager.cpp gui_manager.h
        controls_panel.cpp controls_panel.h
        stats_panel.cpp stats_panel.h
)

target_include_directories(engine-gui PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-gui PUBLIC
        glfw
        imgui
)
