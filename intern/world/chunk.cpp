#include "chunk.hpp"

#include <algorithm>
#include <cmath>

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/noise.hpp"

#include "graphics/texture_atlas/texture_atlas.hpp"
#include "graphics/camera/camera.hpp"
#include "world/chunk_manager.hpp"

struct UnitCube
{
    inline static constexpr glm::vec3 FACE_FRONT[4] =
    {
        {-0.5f, -0.5f, 0.5f},
        { 0.5f, -0.5f, 0.5f},
        { 0.5f,  0.5f, 0.5f},
        {-0.5f,  0.5f, 0.5f}
    };

    inline static constexpr glm::vec3 FACE_BACK[4] =
    {
        { 0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f}
    };

    inline static constexpr glm::vec3 FACE_RIGHT[4] =
    {
        {0.5f, -0.5f,  0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f,  0.5f, -0.5f},
        {0.5f,  0.5f,  0.5f}
    };

    inline static constexpr glm::vec3 FACE_LEFT[4] =
    {
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f}
    };

    inline static constexpr glm::vec3 FACE_TOP[4] =
    {
        {-0.5f, 0.5f,  0.5f},
        { 0.5f, 0.5f,  0.5f},
        { 0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f}
    };

    inline static constexpr glm::vec3 FACE_BOTTOM[4] =
    {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f}
    };
};

VEng::World::Chunk::Chunk(const glm::ivec3 origin)
    : origin_(origin),
      voxels_(WIDTH * DEPTH * HEIGHT, "")
{
}

void VEng::World::Chunk::GenerateTerrain(const int seed)
{
    std::ranges::fill(voxels_, "");

    constexpr float base_height = 100.0f;
    constexpr float scale = 255.0f;

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int z = 0; z < DEPTH; ++z)
        {
            const int world_x = origin_.x + x;
            const int world_z = origin_.z + z;

            glm::vec2 pos(world_x / scale, world_z / scale);

            float max_amplitude = 0.0f;
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float sum = 0.0f;

            for (int i = 0; i < 5; ++i)
            {
                glm::vec2 p = pos * frequency + glm::vec2(seed * 1013, seed * 1619);
                const float n = glm::simplex(p);
                sum += n * amplitude;

                max_amplitude += amplitude;
                frequency *= 2.0f;
                amplitude *= 0.5f;
            }

            const float n = (sum / max_amplitude + 1.0f) / 2.0f;

            const float shaped = std::pow(n, 1.3f);

            float peak = glm::simplex(pos * 0.2f + glm::vec2(seed * 733, seed * 911));
            peak = (peak + 1.0f) * 0.5f;
            const float peak_boost = std::pow(peak, 4.0f);

            const int height = static_cast<int>(
                std::clamp(base_height + shaped * (60.0f + peak_boost * 90.0f), base_height, 255.0f)
            );

            const float snow_noise = glm::simplex(pos * 0.05f + glm::vec2(seed * 17, seed * 37));
            const int snow_offset = static_cast<int>(snow_noise * 10.0f);
            const int snow_line = 175 + snow_offset;
            const int rock_line = snow_line - 10;
            const int snow_base = snow_line - 3;

            for (int y = 0; y <= height; ++y)
            {
                if (y >= snow_base && y <= height)
                {
                    voxels_[Index(x,y,z)] = "snow_block";
                }
                else if (y > rock_line)
                {
                    voxels_[Index(x,y,z)] = "stone_block";
                }
                else if (y == height)
                {
                    voxels_[Index(x,y,z)] = "grass_block";
                }
                else if (y >= height - 3)
                {
                    voxels_[Index(x,y,z)] = "dirt_block";
                }
                else
                {
                    voxels_[Index(x,y,z)] = "stone_block";
                }
            }
        }
    }
}

void VEng::World::Chunk::BuildMesh(const Graphics::TextureAtlas& atlas, const ChunkManager& chunk_manager)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            for (int z = 0; z < DEPTH; ++z)
            {
                AddBlockFaces({x, y, z}, atlas, vertices, indices, chunk_manager);
            }
        }
    }

    UploadMeshData(vertices, indices);
}

void VEng::World::Chunk::Draw(const Graphics::Shader& shader) const
{
    shader.SetUniform("model_matrix", glm::mat4(1.0f));
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
}

void VEng::World::Chunk::AddFace(const FaceContext& ctx,
                                 const Graphics::TextureAtlas& atlas,
                                 std::vector<Vertex>& vertices,
                                 std::vector<unsigned int>& indices)
{
    if (ctx.texture_name.empty()) return;

    const glm::vec4 uv = atlas.GetUV(ctx.texture_name);

    glm::vec2 uv00{ uv.x, uv.y };
    glm::vec2 uv10{ uv.z, uv.y };
    glm::vec2 uv11{ uv.z, uv.w };
    glm::vec2 uv01{ uv.x, uv.w };

    if (ctx.flip_u) std::swap(uv00.x, uv10.x), std::swap(uv01.x, uv11.x);
    if (ctx.flip_v) std::swap(uv00.y, uv01.y), std::swap(uv10.y, uv11.y);

    const unsigned int start = vertices.size();
    vertices.push_back({ ctx.base + ctx.face_vertices[0], uv00, ctx.color });
    vertices.push_back({ ctx.base + ctx.face_vertices[1], uv10, ctx.color });
    vertices.push_back({ ctx.base + ctx.face_vertices[2], uv11, ctx.color });
    vertices.push_back({ ctx.base + ctx.face_vertices[3], uv01, ctx.color });

    indices.push_back(start + 0);
    indices.push_back(start + 1);
    indices.push_back(start + 2);
    indices.push_back(start + 2);
    indices.push_back(start + 3);
    indices.push_back(start + 0);
}

void VEng::World::Chunk::AddBlockFaces(const glm::ivec3& coords,
                                       const Graphics::TextureAtlas& atlas,
                                       std::vector<Vertex>& vertices,
                                       std::vector<unsigned int>& indices,
                                       const ChunkManager& chunk_manager) const
{
    const std::string& block_name = voxels_[Index(coords.x, coords.y, coords.z)];

    if (block_name.empty())
    {
        return;
    }

    const glm::vec3 base = glm::vec3(origin_) + glm::vec3(coords);
    const Graphics::BlockDefinition* block_def = &atlas.GetBlockDefinition(block_name);

    constexpr glm::vec3 default_color{1.0f};

    const std::string& top_tex    = block_def->top_texture_name.empty()    ? "" : block_def->top_texture_name;
    const std::string& bottom_tex = block_def->bottom_texture_name.empty() ? "" : block_def->bottom_texture_name;
    const std::string& side_tex   = block_def->side_texture_name.empty()   ? "" : block_def->side_texture_name;

    const int gx = origin_.x + coords.x;
    const int gy = origin_.y + coords.y;
    const int gz = origin_.z + coords.z;

    if (!chunk_manager.IsSolid(gx + 1, gy, gz))
    {
        AddFace({ base, UnitCube::FACE_RIGHT, side_tex, default_color }, atlas, vertices, indices);
    }

    if (!chunk_manager.IsSolid(gx - 1, gy, gz))
    {
        AddFace({ base, UnitCube::FACE_LEFT, side_tex, default_color, true }, atlas, vertices, indices);
    }

    if (!chunk_manager.IsSolid(gx, gy + 1, gz))
    {
        AddFace({ base, UnitCube::FACE_TOP, top_tex, default_color }, atlas, vertices, indices);
    }

    if (!chunk_manager.IsSolid(gx, gy - 1, gz))
    {
        AddFace({ base, UnitCube::FACE_BOTTOM, bottom_tex, default_color }, atlas, vertices, indices);
    }

    if (!chunk_manager.IsSolid(gx, gy, gz + 1))
    {
        AddFace({ base, UnitCube::FACE_FRONT, side_tex, default_color }, atlas, vertices, indices);
    }

    if (!chunk_manager.IsSolid(gx, gy, gz - 1))
    {
        AddFace({ base, UnitCube::FACE_BACK, side_tex, default_color, true }, atlas, vertices, indices);
    }
}

void VEng::World::Chunk::UploadMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
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

int VEng::World::Chunk::Index(const int x, const int y, const int z)
{
    return x + z * WIDTH + y * WIDTH * DEPTH;
}

bool VEng::World::Chunk::IsSolid(const int x, const int y, const int z) const
{
    if (x < 0 || y < 0 || z < 0 || x >= WIDTH || y >= HEIGHT || z >= DEPTH)
    {
        return false;
    }

    return !voxels_[Index(x,y,z)].empty();
}
