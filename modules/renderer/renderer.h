#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "gui_manager.h"
#include "skybox.h"
#include "world.h"

class Renderer
{
public:
    Renderer();

    void Clear(float r, float g, float b, float a) const;
    void Draw(const World& world, const Camera& camera, const VEng::GUI::Manager& gui_manager) const;

    void SetPolygonMode() const;

private:
    Skybox skybox_;
};

#endif // RENDERER_H
