file(GLOB IMGUI_CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB IMGUI_BACKENDS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/backends/*.cpp)

add_library(imgui STATIC ${IMGUI_CORE_SOURCES} ${IMGUI_BACKENDS_SOURCES})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
)
