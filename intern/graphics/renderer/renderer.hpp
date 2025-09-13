#pragma once

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

        void AddRenderable(const IRenderable& renderable);
        void Render(const Camera& camera) const;

        void Clear(float r, float g, float b, float a) const noexcept;
        void SetPolygonMode() const noexcept;

    private:
        std::vector<std::reference_wrapper<const IRenderable>> renderables_;
    };
}
