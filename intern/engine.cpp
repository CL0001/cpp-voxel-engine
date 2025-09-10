#include "engine.h"

#include "glm/vec3.hpp"

#include "core/clock/clock.h"
#include "gui/stats_panel.h"
#include "gui/controls_panel.h"

VEng::Engine::Engine(const int width, const int height, const char* title)
    : window_(width, height, title),
      camera_(glm::vec3(0.0f, 150.0f, 0.0f), width, height),
      chunk_manager_(ASSETS_PATH "shaders/base.vert",
                     ASSETS_PATH "shaders/base.frag",
                     ASSETS_PATH "textures/blocks/terrain.png",
                     ASSETS_PATH "textures/blocks/terrain_texture_uv.json",
                     ASSETS_PATH "textures/blocks/terrain_block_map.json",
                     16,
                     1,
                     128),
      gui_manager_(window_.GetHandle())
{
    gui_manager_.AddPanel(std::make_unique<VEng::GUI::StatsPanel>());
    gui_manager_.AddPanel(std::make_unique<VEng::GUI::ControlsPanel>());
}

void VEng::Engine::Run()
{
    while (!window_.ShouldClose())
    {
        Core::Clock::Instance().Update();

        std::vector<VEng::GUI::PanelData> data;
        data.emplace_back(VEng::GUI::StatsData{1 / Core::Clock::Instance().GetDeltaTime(), 512.0f});
        data.emplace_back(VEng::GUI::ControlsData{true, false, true, false, false, true, false});

        gui_manager_.Update(data);

        camera_.HandleInput(window_.GetHandle(), Core::Clock::Instance().GetDeltaTime());

        renderer_.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        renderer_.Draw(chunk_manager_, camera_, gui_manager_);

        window_.SwapBuffers();
        window_.PollEvents();
    }
}
