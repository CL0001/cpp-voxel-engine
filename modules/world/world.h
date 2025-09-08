#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "camera.h"
#include "chunk.h"
#include "shader.h"
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
          int seed,
          float scale);

    void Draw(const Camera& camera) const;

    bool IsSolid(int x, int y, int z) const;

private:
    std::vector<Chunk> chunks_;
    Shader shader_;
    TextureAtlas atlas_;

    int seed_;
    float scale_;

    int world_width_chunks_ = 32;
    int world_depth_chunks_ = 32;
};

#endif // WORLD_H
