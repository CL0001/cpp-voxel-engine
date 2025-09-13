#include "renderer.hpp"

#include "glad/glad.h"

VEng::Graphics::Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void VEng::Graphics::Renderer::AddRenderable(const IRenderable& renderable)
{
    renderables_.push_back(std::cref(renderable));
}

void VEng::Graphics::Renderer::Render(const Camera& camera) const
{
    const RenderContext context{camera};

    for (const auto& renderable : renderables_)
    {
        renderable.get().Draw(context);
    }
}

void VEng::Graphics::Renderer::Clear(const float r, const float g, const float b, const float a) const noexcept
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VEng::Graphics::Renderer::SetPolygonMode() const noexcept
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
