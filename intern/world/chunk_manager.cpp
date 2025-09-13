#include "chunk_manager.hpp"

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "graphics/camera/camera.hpp"

static inline int floordiv(const int a, const int b)
{
    return (a >= 0) ? (a / b) : -(( -a + b - 1) / b);
}

VEng::World::ChunkManager::ChunkManager(const ChunkManagerSettings& settings)
    : shader_(settings.vertex_shader_path, settings.fragment_shader_path),
      atlas_(settings.texture_atlas_path, settings.atlas_uv_map_path, settings.atlas_block_map_path, settings.tile_size, settings.texture_unit),
      seed_(settings.seed),
      scale_(settings.scale)
{
    shader_.Use();
    glUniform1i(glGetUniformLocation(shader_.GetProgramId(), "atlas"), settings.texture_unit);
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

void VEng::World::ChunkManager::Draw(const Graphics::RenderContext& context) const
{
    shader_.Use();
    atlas_.Use();

    context.camera.UploadViewProjectionMatrix(shader_.GetProgramId(), "camera_matrix");

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
