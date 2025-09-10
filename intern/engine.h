#pragma once

#include "core/window/window.h"
#include "graphics/camera/camera.h"
#include "graphics/renderer/renderer.h"
#include "gui/gui_manager.h"
#include "world/chunk_manager.h"

namespace VEng
{
    class Engine
    {
    public:
        Engine(int width, int height, const char* title);

        void Run();

    private:
        Core::Window window_;
        Graphics::Camera camera_;
        Graphics::Renderer renderer_;
        World::ChunkManager chunk_manager_;
        GUI::Manager gui_manager_;
    };
}
