#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Cube
{
    glm::vec3 position;

    glm::mat4 GetModelMatrix() const
    {
        return glm::translate(glm::mat4(1.0f), position);
    }
};

#endif // CUBE_H
