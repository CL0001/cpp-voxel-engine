#pragma once

#include "graphics/camera/camera.h"
#include "graphics/skybox/skybox.h"
#include "gui/gui_manager.h"
#include "world/chunk_manager.h"

namespace VEng::Graphics
{
    class Renderer
    {
    public:
        Renderer();

        void Clear(float r, float g, float b, float a) const;
        void Draw(const World::ChunkManager& chunk_manager, const Camera& camera, const GUI::Manager& gui_manager) const;

        void SetPolygonMode() const;

    private:
        VEng::Graphics::Skybox skybox_;
    };
}
