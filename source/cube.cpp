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
        // front face
        0, 1, 2,
        2, 3, 1,

        // left face
        0, 1, 4,
        4, 5, 1,

        // back face
        4, 5, 7,
        7, 6, 5,

        // right face
        2, 3, 7,
        7, 6, 3,

        // bottom face
        0, 4, 2,
        2, 7, 4,

        // top face
        1, 5, 3,
        3, 6, 5
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
