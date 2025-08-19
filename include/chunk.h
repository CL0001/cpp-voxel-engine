#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "glm/vec3.hpp"

#include "shader.h"

class Chunk
{
public:
    Chunk(glm::ivec3 origin, int size);

    void GenerateCubes();
    void BuildMesh();
    void Draw(const Shader& shader) const;

private:
    bool IsSolid(int x, int y, int z) const;
    int Index(int x, int y, int z) const;

    glm::ivec3 origin_;
    int size_;

    std::vector<bool> voxels_;

    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
    int index_count_ = 0;
};

#endif // CHUNK_H
