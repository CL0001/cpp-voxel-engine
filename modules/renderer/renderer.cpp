#include "renderer.h"

#include "glad/glad.h"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const World& world, const Shader& shader, const Camera& camera) const
{
    shader.Use();
    camera.Matrix(45.0f, 0.1f, 100.0f, shader.GetProgramId(), "camera_matrix");
    world.Draw(shader);
}

void Renderer::SetPolygonMode() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
