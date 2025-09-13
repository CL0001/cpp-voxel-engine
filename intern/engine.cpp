#include "engine.hpp"

#include "glm/vec3.hpp"

#include "core/clock/clock.hpp"
#include "gui/stats_panel.hpp"
#include "gui/controls_panel.hpp"

VEng::Engine::Engine(const int width, const int height, const std::string_view title)
    : window_(Core::WindowSettings{
                .width = width,
                .height = height,
                .title = title,
                .enable_vsync = false
            }),
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
      skybox_(Graphics::SkyboxSettings{
                .vertex_shader_path = ASSETS_PATH "shaders/skybox.vert",
                .fragment_shader_path = ASSETS_PATH "shaders/skybox.frag",
                .texture_unit = 1,
                .cubemap_face_paths = {
                    ASSETS_PATH "cubemaps/day/px.jpg",
                    ASSETS_PATH "cubemaps/day/nx.jpg",
                    ASSETS_PATH "cubemaps/day/py.jpg",
                    ASSETS_PATH "cubemaps/day/ny.jpg",
                    ASSETS_PATH "cubemaps/day/pz.jpg",
                    ASSETS_PATH "cubemaps/day/nz.jpg"
                }
            }),
      chunk_manager_(World::ChunkManagerSettings{
                .vertex_shader_path = ASSETS_PATH "shaders/base.vert",
                .fragment_shader_path = ASSETS_PATH "shaders/base.frag",
                .texture_unit = 0,
                .texture_atlas_path = ASSETS_PATH "textures/blocks/terrain.png",
                .atlas_uv_map_path = ASSETS_PATH "textures/blocks/terrain_texture_uv.json",
                .atlas_block_map_path = ASSETS_PATH "textures/blocks/terrain_block_map.json",
                .tile_size = 16,
                .seed = 1,
                .scale = 128
            }),
      gui_manager_(window_.GetHandle())
{
    gui_manager_.AddPanel(GUI::StatsPanel{});
    gui_manager_.AddPanel(GUI::ControlsPanel{});

    renderer_.AddRenderable(skybox_);
    renderer_.AddRenderable(chunk_manager_);
    renderer_.AddRenderable(gui_manager_);
}

void VEng::Engine::Run()
{
    while (!window_.ShouldClose())
    {
        Core::Clock::Instance().Update();

        std::vector<GUI::PanelData> data;
        data.emplace_back(GUI::StatsData{Core::Clock::Instance().GetFrameRate(), 512.0f});
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
