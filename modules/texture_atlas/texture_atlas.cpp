#include "texture_atlas.h"

#include <stdexcept>

#include "glad/glad.h"
#include "glm/vec4.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureAtlas::TextureAtlas(const char* path, const int tile_size)
    : tile_size_(tile_size)
{
    int channels;
    unsigned char* data = stbi_load(path, &atlas_width_, &atlas_height_, &channels, 4);

    if (!data)
    {
        throw std::runtime_error("Failed to load texture atlas: ");
    }

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas_width_, atlas_width_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
}

void TextureAtlas::Use() const
{
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

glm::vec4 TextureAtlas::GetUV(const int tile_index) const
{
    const int tiles_per_row = atlas_width_ / tile_size_;
    int tiles_per_col = atlas_height_ / tile_size_;

    const int row = tile_index / tiles_per_row;
    const int col = tile_index % tiles_per_row;

    const float u_size = static_cast<float>(tile_size_) / atlas_width_;
    const float v_size = static_cast<float>(tile_size_) / atlas_height_;

    const float u_min = col * u_size;
    const float v_min = 1.0f - (row + 1) * v_size; // flip Y
    const float u_max = u_min + u_size;
    const float v_max = v_min + v_size;

    return {u_min, v_min, u_max, v_max};
}
