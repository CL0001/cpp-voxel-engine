#include "chunk_manager.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"

static inline int floordiv(int a, int b)
{
    return (a >= 0) ? (a / b) : -(( -a + b - 1) / b);
}

VEng::World::ChunkManager::ChunkManager(const std::string& vertex_shader_path,
             const std::string& fragment_shader_path,
             const std::string& texture_path,
             const std::string& texture_uv_path,
             const std::string& texture_block_map_path,
             const int tile_size,
             const int seed,
             const float scale)
    : shader_(vertex_shader_path, fragment_shader_path),
      atlas_(texture_path, texture_uv_path, texture_block_map_path, tile_size, 0),
      seed_(seed),
      scale_(scale)
{
    shader_.Use();
    glUniform1i(glGetUniformLocation(shader_.GetProgramId(), "skybox"), 0);
    atlas_.Use();

    chunks_.reserve(world_width_chunks_ * world_depth_chunks_);

    for (int x = 0; x < world_width_chunks_; ++x)
    {
        for (int z = 0; z < world_depth_chunks_; ++z)
        {
            glm::ivec3 origin = { x * Chunk::WIDTH, 0, z * Chunk::DEPTH };
            chunks_.emplace_back(origin);
            chunks_.back().GenerateTerrain(seed_);
        }
    }

    for (int x = 0; x < world_width_chunks_; ++x)
    {
        for (int z = 0; z < world_depth_chunks_; ++z)
        {
            const int index = x * world_depth_chunks_ + z;
            chunks_[index].BuildMesh(atlas_, *this);
        }
    }
}

void VEng::World::ChunkManager::Draw(const Graphics::Camera& camera) const
{
    shader_.Use();
    atlas_.Use();

    camera.UploadViewProjectionMatrix(shader_.GetProgramId(), "camera_matrix");

    for (const auto& chunk : chunks_)
    {
        chunk.Draw(shader_);
    }
}

bool VEng::World::ChunkManager::IsSolid(const int x, const int y, const int z) const
{
    if (y < 0 || y >= Chunk::HEIGHT)
    {
        return false;
    }

    const int cx = floordiv(x, Chunk::WIDTH);
    const int cz = floordiv(z, Chunk::DEPTH);

    if (cx < 0 || cz < 0 || cx >= world_width_chunks_ || cz >= world_depth_chunks_)
    {
        return false;
    }

    const int lx = x - cx * Chunk::WIDTH;
    const int lz = z - cz * Chunk::DEPTH;

    const int chunkIndex = cx * world_depth_chunks_ + cz;

    return chunks_[chunkIndex].IsSolid(lx, y, lz);
}
