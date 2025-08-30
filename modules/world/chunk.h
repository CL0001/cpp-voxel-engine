#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <vector>

#include "glm/vec3.hpp"
#include "FastNoiseLite.h"

#include "geometry.h"
#include "shader.h"
#include "texture_atlas.h"

class Chunk
{
public:
    static constexpr int WIDTH  = 16;
    static constexpr int DEPTH  = 16;
    static constexpr int HEIGHT = 256;

    explicit Chunk(glm::ivec3 origin);

    void GenerateTerrain(const FastNoiseLite& noise);
    void BuildMesh(const TextureAtlas& atlas);
    void Draw(const Shader& shader) const;

private:
    static void AddFace(const glm::vec3& base,
                        const glm::vec3 face_vertices[4],
                        const std::string& texture_name,
                        const TextureAtlas& atlas,
                        std::vector<Vertex>& vertices,
                        std::vector<unsigned int>& indices,
                        bool flip_u = false,
                        bool flip_v = false,
                        const glm::vec3& color = glm::vec3(1.0f));

    void UploadMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    static int Index(int x, int y, int z);
    bool IsSolid(int x, int y, int z) const;

    glm::ivec3 origin_;
    std::vector<std::string> voxels_;

    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
    int index_count_ = 0;
};

#endif // CHUNK_H
