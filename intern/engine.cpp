#include "engine.hpp"

#include "glm/vec3.hpp"

#include "core/clock/clock.hpp"
#include "gui/stats_panel.hpp"
#include "gui/controls_panel.hpp"

VEng::Engine::Engine(const int width, const int height, const char* title)
    : window_(width, height, title),
      camera_(Graphics::CameraSettings{
                .position = glm::vec3(0.0f, 150.0f, 0.0f),
                .orientation = glm::vec3(0.0f, 0.0f, -1.0f),
                .up = glm::vec3(0.0f, 1.0f, 0.0f),
                .width = width,
                .height = height,
                .fov = 45.0f,
                .normal_speed = 10.0f,
                .accelerated_speed = 20.0f,
                .sensitivity = 50.0f
            }),
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
    gui_manager_.AddPanel(new GUI::StatsPanel());
    gui_manager_.AddPanel(new GUI::ControlsPanel());

    renderer_.AddRenderable(std::make_shared<World::ChunkManager>(chunk_manager_));
    renderer_.AddRenderable(std::make_shared<GUI::PanelManager>(gui_manager_));
}

void VEng::Engine::Run()
{
    while (!window_.ShouldClose())
    {
        Core::Clock::Instance().Update();

        std::vector<GUI::PanelData> data;
        data.emplace_back(GUI::StatsData{1 / Core::Clock::Instance().GetDeltaTime(), 512.0f});
        data.emplace_back(GUI::ControlsData{
            glfwGetKey(window_.GetHandle(), GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_D) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_SPACE) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS,
            glfwGetKey(window_.GetHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS
        });

        gui_manager_.Update(data);

        camera_.HandleInput(window_.GetHandle(), Core::Clock::Instance().GetDeltaTime());

        renderer_.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        renderer_.Render(camera_);

        window_.SwapBuffers();
        window_.PollEvents();
    }
}
