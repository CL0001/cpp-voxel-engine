#pragma once

#include "core/window/window.hpp"
#include "graphics/camera/camera.hpp"
#include "graphics/renderer/renderer.hpp"
#include "gui/panel_manager.hpp"
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
        GUI::PanelManager gui_manager_;
    };
}
