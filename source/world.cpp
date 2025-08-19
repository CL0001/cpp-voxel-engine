#include "world.h"

#include "glm/vec3.hpp"

World::World()
{
    chunks_.emplace_back(glm::ivec3(0, 0, 0), 8);
    chunks_[0].BuildMesh();
}

void World::Draw(const Shader& shader) const
{
    for (const auto& chunk : chunks_)
    {
        chunk.Draw(shader);
    }
}
