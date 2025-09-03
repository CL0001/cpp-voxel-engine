#include "world.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "FastNoiseLite.h"

#include "chunk.h"

World::World(const std::string& vertex_shader_path,
             const std::string& fragment_shader_path,
             const std::string& texture_path,
             const std::string& texture_uv_path,
             const std::string& texture_block_map_path,
             const int tile_size)
    : shader_(vertex_shader_path, fragment_shader_path),
      atlas_(texture_path, texture_uv_path, texture_block_map_path, tile_size, 0)
{
    // Problem with texture unit: is set statically for now but should be passed to the atlas later?
    shader_.Use();
    glUniform1i(glGetUniformLocation(shader_.GetProgramId(), "skybox"), 0);

    atlas_.Use();

    FastNoiseLite noise;
    noise.SetSeed(12345);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFrequency(0.003);
    noise.SetFractalOctaves(8);

    chunks_.reserve(16 * 16);

    for (int x = 0; x < 16; ++x)
    {
        for (int z = 0; z < 16; ++z)
        {
            glm::ivec3 origin = {
                x * Chunk::WIDTH,
                0,
                z * Chunk::DEPTH
            };

            chunks_.emplace_back(origin);
            chunks_.back().GenerateTerrain(noise);
            chunks_.back().BuildMesh(atlas_);
        }
    }
}

void World::Draw(const Camera& camera) const
{
    shader_.Use();
    atlas_.Use();

    camera.Matrix(45.0f, 0.1f, 10000.0f, shader_.GetProgramId(), "camera_matrix");

    for (const auto& chunk : chunks_)
    {
        chunk.Draw(shader_);
    }
}
