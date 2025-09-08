#include "engine.h"

#include "glm/vec3.hpp"

#include "clock.h"

Engine::Engine(const int width, const int height, const char* title)
    : window_(width, height, title),
      camera_(glm::vec3(0.0f, 150.0f, 0.0f), width, height),
      world_(ASSETS_PATH "shaders/base.vert",
             ASSETS_PATH "shaders/base.frag",
             ASSETS_PATH "textures/blocks/terrain.png",
             ASSETS_PATH "textures/blocks/terrain_texture_uv.json",
             ASSETS_PATH "textures/blocks/terrain_block_map.json",
             16,
             1,
             128),
      gui_(window_.GetHandle())
{
}

void Engine::Run()
{
    while (!window_.ShouldClose())
    {
        Clock::Instance().Update();

        camera_.HandleInput(window_.GetHandle(), Clock::Instance().GetDeltaTime());

        renderer_.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        renderer_.Draw(world_, camera_, gui_);

        window_.SwapBuffers();
        window_.PollEvents();
    }
}
