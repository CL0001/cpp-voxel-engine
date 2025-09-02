#include "renderer.h"

#include "glad/glad.h"

#include "clock.h"
#include "gui.h"

Renderer::Renderer()
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

void Renderer::Draw(const World& world, const Shader& shader, const Camera& camera, const GUI& gui) const
{
    //renderer_.SetPolygonMode();

    shader.Use();
    shader.SetUniform("atlas", 0);

    camera.Matrix(45.0f, 0.1f, 10000.0f, shader.GetProgramId(), "camera_matrix");

    world.Draw(shader);
    gui.Draw(1 / Clock::Instance().GetDeltaTime());
}

void Renderer::SetPolygonMode() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
