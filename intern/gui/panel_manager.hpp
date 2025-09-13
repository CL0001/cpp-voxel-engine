#pragma once

#include <vector>
#include <memory>

#include "glfw/glfw3.h"

#include "graphics/renderer/renderer.hpp"
#include "igui_panel.hpp"

namespace VEng::GUI
{
    class PanelManager final : public Graphics::IRenderable
    {
    public:
        explicit PanelManager(GLFWwindow* window);
        ~PanelManager() override;

        void Update(const std::vector<PanelData>& panel_data);
        void Draw(const Graphics::RenderContext& context) const override;

        template <typename PanelType>
        void AddPanel(PanelType panel) noexcept
        {
            panels_.emplace_back(std::make_unique<PanelType>(std::move(panel)));
        }

    private:
        std::vector<std::unique_ptr<IGUIPanel>> panels_;
    };
}
