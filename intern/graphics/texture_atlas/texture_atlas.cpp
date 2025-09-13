#include "texture_atlas.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "glad/glad.h"
#include "json.hpp"

#include "stb_image.h"

VEng::Graphics::TextureAtlas::TextureAtlas(const std::filesystem::path& texture_path,
                                           const std::filesystem::path& texture_uv_path,
                                           const std::filesystem::path& texture_block_map_path,
                                           int tile_size,
                                           int texture_unit)
    : texture_unit_(texture_unit), tile_size_(tile_size)
{
    int nr_channels;

    stbi_set_flip_vertically_on_load(true);

    if (unsigned char* data = stbi_load(texture_path.string().c_str(), &width_, &height_, &nr_channels, 4))
    {
        glGenTextures(1, &texture_id_);
        glBindTexture(GL_TEXTURE_2D, texture_id_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        throw std::runtime_error("Failed to load texture atlas: " + texture_path.string());
    }

    std::ifstream uv_file(texture_uv_path);
    if (!uv_file.is_open())
    {
        throw std::runtime_error("Failed to open UV JSON: " + texture_uv_path.string());
    }

    nlohmann::json uv_json;
    uv_file >> uv_json;

    for (auto& [key, value] : uv_json.items())
    {
        if (value.is_object()
            && value.contains("u")
            && value.contains("v")
            && !value["u"].is_null()
            && !value["v"].is_null())
        {
            texture_uv_map_[key] = { value["u"].get<int>(), value["v"].get<int>() };
        }
        else
        {
            std::cerr << "[Warning] Invalid UV entry for key: " << key << "\n";
        }
    }

    std::ifstream block_file(texture_block_map_path);
    if (!block_file.is_open())
        throw std::runtime_error("Failed to open block map JSON: " + texture_block_map_path.string());

    nlohmann::json block_json;
    block_file >> block_json;

    for (auto& [block_name, block_data] : block_json.items())
    {
        BlockDefinition def;
        def.block_name = block_name;

        if (block_data.contains("textures") && block_data["textures"].is_object())
        {
            const auto& textures = block_data["textures"];
            def.top_texture_name    = textures.value("top", "");
            def.side_texture_name   = textures.value("side", "");
            def.bottom_texture_name = textures.value("bottom", "");
        }
        else
        {
            std::cerr << "[Warning] Block '" << block_name << "' has no valid textures object, using empty strings.\n";
            def.top_texture_name = def.side_texture_name = def.bottom_texture_name = "";
        }

        block_map_[block_name] = def;
    }
}

VEng::Graphics::TextureAtlas::~TextureAtlas()
{
    glDeleteTextures(1, &texture_id_);
}

void VEng::Graphics::TextureAtlas::Use() const
{
    glActiveTexture(GL_TEXTURE0 + texture_unit_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

glm::vec4 VEng::Graphics::TextureAtlas::GetUV(const std::string& tile_key) const
{
    const auto it = texture_uv_map_.find(tile_key);

    if (it == texture_uv_map_.end())
    {
        throw std::runtime_error("Texture key not found in atlas: " + tile_key);
    }

    const int u = it->second.u;
    const int v = it->second.v;

    const float u_size = static_cast<float>(tile_size_) / width_;
    const float v_size = static_cast<float>(tile_size_) / height_;

    const float u_min = u * u_size;
    const float v_min = 1.0f - (v + 1) * v_size; // flip Y
    const float u_max = u_min + u_size;
    const float v_max = v_min + v_size;

    return { u_min, v_min, u_max, v_max };
}

const VEng::Graphics::BlockDefinition& VEng::Graphics::TextureAtlas::GetBlockDefinition(const std::string& block_name) const
{
    const auto it = block_map_.find(block_name);

    if (it == block_map_.end())
    {
        throw std::runtime_error("Block definition not found: " + block_name);
    }

    return it->second;
}
