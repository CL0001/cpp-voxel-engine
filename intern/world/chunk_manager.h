#pragma once

#include <string>
#include <vector>

#include "graphics/shader/shader.hpp"
#include "graphics/texture_atlas/texture_atlas.hpp"

#include "chunk.h"
#include "graphics/renderer/renderer.hpp"

namespace VEng::World
{
    class ChunkManager final : public Graphics::IRenderable
    {
    public:
        ChunkManager(const std::string& vertex_shader_path,
                     const std::string& fragment_shader_path,
                     const std::string& texture_path,
                     const std::string& texture_uv_path,
                     const std::string& texture_block_map_path,
                     int tile_size,
                     int seed,
                     float scale);

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
