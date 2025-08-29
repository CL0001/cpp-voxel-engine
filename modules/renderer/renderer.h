#ifndef RENDERER_H
#define RENDERER_H

#include "../world/world.h"
#include "shader.h"
#include "camera.h"

class Renderer
{
public:
    Renderer();

    void Clear(float r, float g, float b, float a) const;
    void Draw(const World& world, const Shader& shader, const Camera& camera) const;

    void SetPolygonMode() const;
};


#endif //RENDERER_H
