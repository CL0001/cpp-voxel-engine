#include "cube.h"

#include "glad/glad.h"

Cube::Cube()
{
    constexpr float vertices[] = {
        // positions
        -0.5f, -0.5f,  0.5f, // front left bottom
        -0.5f,  0.5f,  0.5f, // front left top
         0.5f, -0.5f,  0.5f, // front right bottom
         0.5f,  0.5f,  0.5f, // front right top
        -0.5f, -0.5f, -0.5f, // back left bottom
        -0.5f,  0.5f, -0.5f, // back left top
         0.5f, -0.5f, -0.5f, // back right bottom
         0.5f,  0.5f, -0.5f, // back right top
    };

    constexpr unsigned int indices[] = {
        // front face (CCW)
        0, 1, 2,
        1, 3, 2,

        // left face (CCW)
        4, 5, 0,
        5, 1, 0,

        // back face (CCW)
        6, 7, 4,
        7, 5, 4,

        // right face (CCW)
        2, 3, 6,
        3, 7, 6,

        // bottom face (CCW)
        0, 2, 4,
        2, 6, 4,

        // top face (CCW)
        1, 5, 3,
        5, 7, 3
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // TODO: Add color pointer

    // TODO: Add texture pointer

    glBindVertexArray(0);
}

void Cube::Draw() const
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
