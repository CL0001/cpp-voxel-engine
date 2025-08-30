#include "chunk.h"

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "texture_atlas.h"
#include <iostream>

Chunk::Chunk(const glm::ivec3 origin)
    : origin_(origin),
      voxels_(WIDTH * DEPTH * HEIGHT, "")
{
}

void Chunk::GenerateTerrain(const FastNoiseLite& noise)
{
    std::fill(voxels_.begin(), voxels_.end(), "");

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int z = 0; z < DEPTH; ++z)
        {
            const int world_x = origin_.x + x;
            const int world_z = origin_.z + z;

            const float n = noise.GetNoise(static_cast<float>(world_x), static_cast<float>(world_z));
            const int height = static_cast<int>((n + 1.0f) * 0.5f * (HEIGHT - 1));

            for (int y = 0; y <= height; ++y)
            {
                if (y == height) voxels_[Index(x, y, z)] = "grass_block";
                else if (y >= height - 3) voxels_[Index(x, y, z)] = "dirt_block";
                else voxels_[Index(x, y, z)] = "stone_block";
            }
        }
    }
}

void Chunk::BuildMesh(const TextureAtlas& atlas)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    constexpr glm::vec3 plainsGreen{ 0.35f, 1.0f, 0.35f };
    constexpr glm::vec3 defaultColor{ 1.0f };

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            for (int z = 0; z < DEPTH; ++z)
            {
                const std::string& block_name = voxels_[Index(x, y, z)];
                if (block_name.empty()) continue;

                glm::vec3 base = glm::vec3(origin_) + glm::vec3(x, y, z);

                const BlockDefinition* block_def = nullptr;

                try
                {
                    block_def = &atlas.GetBlockDefinition(block_name);
                }
                catch (const std::runtime_error&)
                {
                    continue;
                }

                std::string top_tex    = block_def->top_texture_name.empty()    ? "" : block_def->top_texture_name;
                std::string bottom_tex = block_def->bottom_texture_name.empty() ? "" : block_def->bottom_texture_name;
                std::string side_tex   = block_def->side_texture_name.empty()   ? "" : block_def->side_texture_name;

                if (!IsSolid(x + 1, y, z)) AddFace(base, UnitCube::FACE_RIGHT, side_tex, atlas, vertices, indices, false, false, defaultColor);
                if (!IsSolid(x - 1, y, z)) AddFace(base, UnitCube::FACE_LEFT,  side_tex, atlas, vertices, indices, true,  false, defaultColor);

                if (!IsSolid(x, y + 1, z))
                {
                    glm::vec3 color = (block_name == "grass_block") ? plainsGreen : defaultColor;
                    AddFace(base, UnitCube::FACE_TOP, top_tex, atlas, vertices, indices, false, false, color);
                }

                if (!IsSolid(x, y - 1, z)) AddFace(base, UnitCube::FACE_BOTTOM, bottom_tex, atlas, vertices, indices, false, false, defaultColor);
                if (!IsSolid(x, y, z + 1)) AddFace(base, UnitCube::FACE_FRONT, side_tex, atlas, vertices, indices, false, false, defaultColor);
                if (!IsSolid(x, y, z - 1)) AddFace(base, UnitCube::FACE_BACK,  side_tex, atlas, vertices, indices, true,  false, defaultColor);
            }
        }
    }

    UploadMeshData(vertices, indices);
}

void Chunk::Draw(const Shader& shader) const
{
    shader.SetUniform("model_matrix", glm::mat4(1.0f));
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
}

void Chunk::AddFace(const glm::vec3& base,
                    const glm::vec3 face_vertices[4], const std::string& texture_name,
                    const TextureAtlas& atlas,
                    std::vector<Vertex>& vertices,
                    std::vector<unsigned int>& indices,
                    const bool flip_u,
                    const bool flip_v,
                    const glm::vec3& color)
{
    if (texture_name.empty()) return;

    glm::vec4 uv;
    try
    {
        uv = atlas.GetUV(texture_name);
    }
    catch (const std::runtime_error&)
    {
        return;
    }

    glm::vec2 uv00 = { uv.x, uv.y };
    glm::vec2 uv10 = { uv.z, uv.y };
    glm::vec2 uv11 = { uv.z, uv.w };
    glm::vec2 uv01 = { uv.x, uv.w };

    if (flip_u) std::swap(uv00.x, uv10.x), std::swap(uv01.x, uv11.x);
    if (flip_v) std::swap(uv00.y, uv01.y), std::swap(uv10.y, uv11.y);

    const unsigned int start = vertices.size();
    vertices.push_back({ base + face_vertices[0], uv00, color });
    vertices.push_back({ base + face_vertices[1], uv10, color });
    vertices.push_back({ base + face_vertices[2], uv11, color });
    vertices.push_back({ base + face_vertices[3], uv01, color });

    indices.push_back(start + 0);
    indices.push_back(start + 1);
    indices.push_back(start + 2);
    indices.push_back(start + 2);
    indices.push_back(start + 3);
    indices.push_back(start + 0);
}

void Chunk::UploadMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    index_count_ = indices.size();

    if (vao_ == 0)
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);
    }

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

int Chunk::Index(const int x, const int y, const int z)
{
    return x + z * WIDTH + y * WIDTH * DEPTH;
}

bool Chunk::IsSolid(const int x, const int y, const int z) const
{
    if ( x < 0 || y < 0 || z < 0 || x >= WIDTH || y >= HEIGHT || z >= DEPTH) return false;

    return !voxels_[Index(x,y,z)].empty();
}
