#pragma once

#include <memory>
#include <vector>

namespace VEng::Graphics
{
    class Camera;

    struct RenderContext
    {
        const Camera& camera;
    };

    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;
        virtual void Draw(const RenderContext& context) const = 0;
    };

    class Renderer
    {
    public:
        Renderer();

        void AddRenderable(const std::shared_ptr<IRenderable>& renderable) noexcept;
        void Render(const Camera& camera) const noexcept;

        void Clear(float r, float g, float b, float a) const noexcept;
        void SetPolygonMode() const noexcept;

    private:
        std::vector<std::shared_ptr<IRenderable>> renderables_;
    };
}
