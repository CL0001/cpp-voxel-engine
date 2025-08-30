#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <string>
#include <unordered_map>

#include "glm/vec4.hpp"

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
                 int tile_size);

    void Use() const;

    glm::vec4 GetUV(const std::string& tile_key) const;

    const BlockDefinition& GetBlockDefinition(const std::string& block_name) const;

private:
    unsigned int texture_id_;
    int atlas_width_;
    int atlas_height_;
    int tile_size_;

    std::unordered_map<std::string, TileUV> texture_uv_map_;

    std::unordered_map<std::string, BlockDefinition> block_map_;
};

#endif // TEXTURE_ATLAS_H
