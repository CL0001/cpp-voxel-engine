#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 color;
};

struct UnitCube
{
    static constexpr glm::vec3 FACE_FRONT[4] = {
        {-0.5, -0.5, 0.5},
        { 0.5, -0.5, 0.5},
        { 0.5,  0.5, 0.5},
        {-0.5,  0.5, 0.5}
    };
    static constexpr glm::vec3 FACE_BACK[4] = {
        { 0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5,  0.5, -0.5},
        { 0.5,  0.5, -0.5}
    };
    static constexpr glm::vec3 FACE_RIGHT[4] = {
        {0.5, -0.5,  0.5},
        {0.5, -0.5, -0.5},
        {0.5,  0.5, -0.5},
        {0.5,  0.5,  0.5}
    };
    static constexpr glm::vec3 FACE_LEFT[4] = {
        {-0.5, -0.5, -0.5},
        {-0.5, -0.5,  0.5},
        {-0.5,  0.5,  0.5},
        {-0.5,  0.5, -0.5}
    };
    static constexpr glm::vec3 FACE_TOP[4] = {
        {-0.5, 0.5,  0.5},
        { 0.5, 0.5,  0.5},
        { 0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5}
    };
    static constexpr glm::vec3 FACE_BOTTOM[4] = {
        {-0.5, -0.5, -0.5},
        { 0.5, -0.5, -0.5},
        { 0.5, -0.5,  0.5},
        {-0.5, -0.5,  0.5}
    };
};

#endif // GEOMETRY_H
