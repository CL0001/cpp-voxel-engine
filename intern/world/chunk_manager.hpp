#pragma once

#include <vector>

#include "graphics/shader/shader.hpp"
#include "graphics/texture_atlas/texture_atlas.hpp"

#include "chunk.hpp"
#include "graphics/renderer/renderer.hpp"

namespace VEng::World
{
    struct ChunkManagerSettings
    {
        std::filesystem::path vertex_shader_path;
        std::filesystem::path fragment_shader_path;
        int texture_unit;
        std::filesystem::path texture_atlas_path;
        std::filesystem::path atlas_uv_map_path;
        std::filesystem::path atlas_block_map_path;
        int tile_size;
        int seed;
        float scale;
        int render_distance;
    };

    class ChunkManager final : public Graphics::IRenderable
    {
    public:
        ChunkManager(const ChunkManagerSettings& settings);

        void Draw(const Graphics::RenderContext& context) const override;

        bool IsSolid(int x, int y, int z) const;

    private:
        std::vector<Chunk> chunks_;
        Graphics::Shader shader_;
        Graphics::TextureAtlas atlas_;

        int seed_;
        float scale_;

        int world_width_chunks_ = 32;
        int world_depth_chunks_ = 32;
    };
}
