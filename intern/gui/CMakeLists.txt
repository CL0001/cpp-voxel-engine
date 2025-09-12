add_library(engine-gui STATIC
        panel_manager.cpp panel_manager.hpp
        controls_panel.cpp controls_panel.hpp
        stats_panel.cpp stats_panel.hpp
)

target_include_directories(engine-gui PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-gui PUBLIC
        glfw
        imgui
        engine-graphics
)
