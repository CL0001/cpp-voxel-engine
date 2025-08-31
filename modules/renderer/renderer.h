#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "gui.h"
#include "shader.h"
#include "world.h"

class Renderer
{
public:
    Renderer();

    void Clear(float r, float g, float b, float a) const;
    void Draw(const World& world, const Shader& shader, const Camera& camera, const GUI& gui) const;

    void SetPolygonMode() const;
};

#endif // RENDERER_H
