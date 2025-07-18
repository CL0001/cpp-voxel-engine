set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/source/glad.c)

add_library(glad STATIC ${GLAD_SRC})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
