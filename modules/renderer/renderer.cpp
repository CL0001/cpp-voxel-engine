#include "renderer.h"

#include "glad/glad.h"

#include "clock.h"
#include "gui.h"

Renderer::Renderer()
    : skybox_(ASSETS_PATH "shaders/skybox.vert",
              ASSETS_PATH "shaders/skybox.frag",
              1,
              {ASSETS_PATH "cubemaps/day/px.jpg", ASSETS_PATH "cubemaps/day/nx.jpg", ASSETS_PATH "cubemaps/day/py.jpg", ASSETS_PATH "cubemaps/day/ny.jpg", ASSETS_PATH "cubemaps/day/pz.jpg", ASSETS_PATH "cubemaps/day/nz.jpg"})
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::Clear(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const World& world, const Camera& camera, const GUI& gui) const
{
    skybox_.Draw(camera);

    world.Draw(camera);
    gui.Draw(1 / Clock::Instance().GetDeltaTime());
}

void Renderer::SetPolygonMode() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
