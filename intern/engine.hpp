#pragma once

#include <string_view>

#include "core/window/window.hpp"
#include "graphics/camera/camera.hpp"
#include "graphics/renderer/renderer.hpp"
#include "graphics/skybox/skybox.hpp"
#include "gui/panel_manager.hpp"
#include "world/chunk_manager.hpp"

namespace VEng
{
    class Engine
    {
    public:
        Engine(int width, int height, std::string_view title);

        void Run();

    private:
        Core::Window window_;
        Graphics::Camera camera_;
        Graphics::Renderer renderer_;
        Graphics::Skybox skybox_;
        World::ChunkManager chunk_manager_;
        GUI::PanelManager gui_manager_;
    };
}
