add_library(engine STATIC
        engine.cpp engine.h
)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine PUBLIC
        engine-core
        engine-graphics
        engine-gui
        engine-world
        spdlog
)

if (WIN32)
    target_link_libraries(engine PUBLIC opengl32)
elseif (APPLE)
    target_link_libraries(engine PUBLIC "-framework OpenGL")
else()
    target_link_libraries(engine PUBLIC GL)
endif()

target_compile_definitions(engine PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")
