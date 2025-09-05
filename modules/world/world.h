#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "FastNoiseLite.h"

#include "camera.h"
#include "shader.h"
#include "chunk.h"
#include "texture_atlas.h"

class World
{
public:
    World(const std::string& vertex_shader_path,
          const std::string& fragment_shader_path,
          const std::string& texture_path,
          const std::string& texture_uv_path,
          const std::string& texture_block_map_path,
          int tile_size,
          int seed);

    void Draw(const Camera& camera) const;

private:
    std::vector<Chunk> chunks_;
    Shader shader_;
    TextureAtlas atlas_;

    FastNoiseLite noise_;
};

#endif // WORLD_H
