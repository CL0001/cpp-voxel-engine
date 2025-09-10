#pragma once

#include <string>
#include <unordered_map>

#include "glm/vec4.hpp"

namespace VEng::Graphics
{
    struct TileUV
    {
        int u;
        int v;
    };

    struct BlockDefinition
    {
        std::string block_name;
        std::string top_texture_name;
        std::string side_texture_name;
        std::string bottom_texture_name;
    };

    class TextureAtlas
    {
    public:
        TextureAtlas(const std::string& texture_path,
                     const std::string& texture_uv_path,
                     const std::string& texture_block_map_path,
                     int tile_size,
                     unsigned int texture_unit);

        ~TextureAtlas();

        void Use() const;

        glm::vec4 GetUV(const std::string& tile_key) const;
        const BlockDefinition& GetBlockDefinition(const std::string& block_name) const;

    private:
        unsigned int texture_id_;
        unsigned int texture_unit_;
        int width_;
        int height_;
        int tile_size_;

        std::unordered_map<std::string, TileUV> texture_uv_map_;
        std::unordered_map<std::string, BlockDefinition> block_map_;
    };
}
