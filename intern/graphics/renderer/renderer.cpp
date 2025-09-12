#include "renderer.hpp"

#include "glad/glad.h"

#include "graphics/skybox/skybox.hpp"

VEng::Graphics::Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void VEng::Graphics::Renderer::AddRenderable(const std::shared_ptr<IRenderable>& renderable) noexcept
{
    renderables_.push_back(renderable);
}

void VEng::Graphics::Renderer::Render(const Camera& camera) const noexcept
{
    const RenderContext context{camera};

    // const Skybox skybox_(SkyboxSettings{
    //       .vertex_shader_path = ASSETS_PATH "shaders/skybox.vert",
    //       .fragment_shader_path = ASSETS_PATH "shaders/skybox.frag",
    //       .texture_unit = 1,
    //       .cubemap_face_paths = {
    //           ASSETS_PATH "cubemaps/day/px.jpg",
    //           ASSETS_PATH "cubemaps/day/nx.jpg",
    //           ASSETS_PATH "cubemaps/day/py.jpg",
    //           ASSETS_PATH "cubemaps/day/ny.jpg",
    //           ASSETS_PATH "cubemaps/day/pz.jpg",
    //           ASSETS_PATH "cubemaps/day/nz.jpg"
    //       }
    //   });
    // skybox_.Draw(camera);

    for (const auto& renderable : renderables_)
    {
        renderable->Draw(context);
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
