add_library(shader STATIC shader.cpp)

target_include_directories(shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(shader glad glm spdlog)