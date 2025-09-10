add_library(engine-core STATIC
        clock/clock.cpp clock/clock.h
        window/window.cpp window/window.h
)

target_include_directories(engine-core PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-core PUBLIC
        glfw
        glad
        spdlog
)
