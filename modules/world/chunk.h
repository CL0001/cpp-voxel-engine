#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "glm/vec3.hpp"
#include "FastNoiseLite.h"

#include "shader.h"
#include "texture_atlas.h"

class Chunk {
public:
    static constexpr int WIDTH  = 16;
    static constexpr int DEPTH  = 16;
    static constexpr int HEIGHT = 256;

    Chunk(glm::ivec3 origin);

    void GenerateTerrain(const FastNoiseLite& noise);
    void BuildMesh(const TextureAtlas& atlas);
    void Draw(const Shader& shader) const;

private:
    int Index(int x, int y, int z) const;

    bool IsSolid(int x, int y, int z) const;

    int GetBlockTileIndex(int x, int y, int z) const;

    glm::ivec3 origin_;
    std::vector<bool> voxels_;

    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
    int index_count_ = 0;
};

#endif // CHUNK_H
