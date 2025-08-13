#include "world.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"

#include "cube.h"
#include "shader.h"

World::World()
{
    constexpr int size = 3;

    for (int x = 0; x < size; ++x)
    {
        for (int y = 0; y < size; ++y)
        {
            for (int z = 0; z < size; ++z)
            {
                cubes_.emplace_back(glm::vec3(x, y, z));
            }
        }
    }
}

void World::Draw(const Shader& shader) const
{
    mesh_.Bind();

    for (const Cube& cube : cubes_)
    {
        shader.SetUniform("model_matrix", cube.GetModelMatrix());
        glDrawElements(GL_TRIANGLES, mesh_.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    }
}
