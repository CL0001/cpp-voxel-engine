#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "cube.h"
#include "cube_mesh.h"
#include "shader.h"

class World
{
public:
    World();

    void Draw(const Shader& shader) const;

private:
    CubeMesh mesh_;
    std::vector<Cube> cubes_;
};

#endif // WORLD_H
