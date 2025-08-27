#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "../modules/shader/shader.h"
#include "chunk.h"

class World
{
public:
    World();

    void Draw(const Shader& shader) const;

private:
    std::vector<Chunk> chunks_;
};

#endif // WORLD_H
