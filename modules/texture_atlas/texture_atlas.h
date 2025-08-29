#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include "glm/vec4.hpp"

class TextureAtlas
{
public:
    TextureAtlas(const char* path, int tile_size);

    void Use() const;

    glm::vec4 GetUV(int tile_index) const;

private:
    unsigned int texture_id_;
    int atlas_width_;
    int atlas_height_;
    int tile_size_;
};

#endif // TEXTURE_ATLAS_H
