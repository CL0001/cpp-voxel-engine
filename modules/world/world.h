#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "shader.h"
#include "chunk.h"
#include "texture_atlas.h"

class World
{
public:
    World(const std::string& texture_path,
          const std::string& texture_uv_path,
          const std::string& texture_block_map_path,
          int tile_size);

    void Draw(const Shader& shader) const;

private:
    std::vector<Chunk> chunks_;
    TextureAtlas atlas_;
};

#endif // WORLD_H
