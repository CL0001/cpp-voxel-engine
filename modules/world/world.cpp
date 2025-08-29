#include "world.h"

#include "glm/vec3.hpp"
#include "FastNoiseLite.h"

#include "chunk.h"

World::World(const char* texture_atlas_path, const int tile_size)
    : atlas_(texture_atlas_path, tile_size)
{
    atlas_.Use();

    FastNoiseLite noise;
    noise.SetSeed(14);
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

void World::Draw(const Shader& shader) const
{
    for (const auto& chunk : chunks_)
    {
        chunk.Draw(shader);
    }
}
