#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "shader.h"
#include "chunk.h"
#include "texture_atlas.h"

class World
{
public:
    World(const char* texture_atlas_path, int tile_size);

    void Draw(const Shader& shader) const;

private:
    std::vector<Chunk> chunks_;
    TextureAtlas atlas_;
};

#endif // WORLD_H
