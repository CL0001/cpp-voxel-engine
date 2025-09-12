add_library(engine-core STATIC
        clock/clock.cpp clock/clock.hpp
        window/window.cpp window/window.hpp
)

target_include_directories(engine-core PUBLIC
        ${INTERN_DIR}
)

target_link_libraries(engine-core PUBLIC
        glfw
        glad
        spdlog
)
