#include "cube_mesh.h"

#include "glad/glad.h"

constexpr float origin_cube_vertices[] = {
    -0.5f, -0.5f,  0.5f, // 0 front left bottom
    -0.5f,  0.5f,  0.5f, // 1 front left top
     0.5f, -0.5f,  0.5f, // 2 front right bottom
     0.5f,  0.5f,  0.5f, // 3 front right top
    -0.5f, -0.5f, -0.5f, // 4 back left bottom
    -0.5f,  0.5f, -0.5f, // 5 back left top
     0.5f, -0.5f, -0.5f, // 6 back right bottom
     0.5f,  0.5f, -0.5f  // 7 back right top
};

constexpr unsigned int origin_cube_indices[] = {
    0, 1, 2, // front face
    1, 3, 2,
    4, 5, 0, // left face
    5, 1, 0,
    6, 7, 4, // back face
    7, 5, 4,
    2, 3, 6, // right face
    3, 7, 6,
    0, 2, 4, // bottom face
    2, 6, 4,
    1, 5, 3, // top face
    5, 7, 3
};

CubeMesh::CubeMesh()
{
    glGenBuffers(1, &vbo_);
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(origin_cube_vertices), origin_cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(origin_cube_indices), origin_cube_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

CubeMesh::~CubeMesh()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

void CubeMesh::Bind() const
{
    glBindVertexArray(vao_);
}

unsigned int CubeMesh::GetIndexCount() const
{
    return index_count_;
}
