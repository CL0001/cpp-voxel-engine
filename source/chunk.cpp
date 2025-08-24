#include "chunk.h"

#include "glad/glad.h"

struct Vertex {
    glm::vec3 pos;
};

Chunk::Chunk(const glm::ivec3 origin)
    : origin_(origin),
      voxels_(WIDTH * DEPTH * HEIGHT, true)
{
}

void Chunk::GenerateTerrain(const FastNoiseLite& noise)
{
    std::fill(voxels_.begin(), voxels_.end(), false);

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
                voxels_[Index(x, y, z)] = true;
            }
        }
    }
}

void Chunk::BuildMesh()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    auto AddFace = [&](const glm::vec3 base, const glm::vec3 face_vertices[4])
    {
        const unsigned int start = vertices.size();

        for (int i = 0; i < 4; ++i)
        {
            vertices.push_back({base + face_vertices[i]});
        }

        indices.push_back(start + 0);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
        indices.push_back(start + 0);
    };

    // cube face templates (unit cube, centered at 0,0,0)
    static constexpr glm::vec3 FACE_RIGHT[4] = {
        {0.5, -0.5, -0.5},
        {0.5,  0.5, -0.5},
        {0.5,  0.5,  0.5},
        {0.5, -0.5,  0.5}
    };
    static constexpr glm::vec3 FACE_LEFT[4] = {
        {-0.5, -0.5,  0.5},
        {-0.5,  0.5,  0.5},
        {-0.5,  0.5, -0.5},
        {-0.5, -0.5, -0.5}
    };
    static constexpr glm::vec3 FACE_TOP[4] = {
        {-0.5, 0.5,  0.5},
        { 0.5, 0.5,  0.5},
        { 0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5}
    };
    static constexpr glm::vec3 FACE_BOTTOM[4] = {
        {-0.5, -0.5, -0.5},
        { 0.5, -0.5, -0.5},
        { 0.5, -0.5,  0.5},
        {-0.5, -0.5,  0.5}
    };
    static constexpr glm::vec3 FACE_FRONT[4] = {
        {-0.5, -0.5, 0.5},
        { 0.5, -0.5, 0.5},
        { 0.5,  0.5, 0.5},
        {-0.5,  0.5, 0.5}
    };
    static constexpr glm::vec3 FACE_BACK[4] = {
        { 0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5,  0.5, -0.5},
        { 0.5,  0.5, -0.5}
    };

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            for (int z = 0; z < DEPTH; ++z)
            {
                if (!IsSolid(x, y, z))
                {
                    continue;
                }

                const glm::vec3 base = glm::vec3(origin_) + glm::vec3(x,y,z);

                if (!IsSolid(x + 1, y, z)) AddFace(base, FACE_RIGHT);
                if (!IsSolid(x - 1, y, z)) AddFace(base, FACE_LEFT);
                if (!IsSolid(x, y + 1, z)) AddFace(base, FACE_TOP);
                if (!IsSolid(x, y - 1, z)) AddFace(base, FACE_BOTTOM);
                if (!IsSolid(x, y, z + 1)) AddFace(base, FACE_FRONT);
                if (!IsSolid(x, y, z - 1)) AddFace(base, FACE_BACK);
            }
        }
    }

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Chunk::Draw(const Shader& shader) const
{
    shader.SetUniform("model_matrix", glm::mat4(1.0f));
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
}

bool Chunk::IsSolid(const int x, const int y, const int z) const
{
    if (x < 0 || y < 0 || z < 0 || x >= WIDTH || y >= HEIGHT || z >= DEPTH)
    {
        return false;
    }

    return voxels_[Index(x, y, z)];
}

int Chunk::Index(const int x, const int y, const int z) const
{
    return x + z * WIDTH + y * WIDTH * DEPTH;
}
