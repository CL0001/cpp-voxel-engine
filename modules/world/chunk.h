#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>
#include "glm/vec3.hpp"
#include "shader.h"
#include "texture_atlas.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 color;
};

struct FaceContext
{
    const glm::vec3& base;
    const glm::vec3* face_vertices;
    std::string texture_name;
    glm::vec3 color;
    bool flip_u = false;
    bool flip_v = false;
};

class Chunk
{
public:
    static constexpr int WIDTH  = 16;
    static constexpr int DEPTH  = 16;
    static constexpr int HEIGHT = 256;

    explicit Chunk(glm::ivec3 origin);

    void GenerateTerrain(int seed);
    void BuildMesh(const TextureAtlas& atlas);
    void Draw(const Shader& shader) const;

private:
    static void AddFace(const FaceContext& ctx,
                        const TextureAtlas& atlas,
                        std::vector<Vertex>& vertices,
                        std::vector<unsigned int>& indices);
    static int Index(int x, int y, int z);

    void AddBlockFaces(const glm::ivec3& coords,
                       const TextureAtlas& atlas,
                       std::vector<Vertex>& vertices,
                       std::vector<unsigned int>& indices) const;
    void UploadMeshData(const std::vector<Vertex>& vertices,
                        const std::vector<unsigned int>& indices);
    bool IsSolid(int x, int y, int z) const;

    glm::ivec3 origin_;
    std::vector<std::string> voxels_;

    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
    int index_count_ = 0;
};

#endif // CHUNK_H
