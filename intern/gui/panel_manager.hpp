#pragma once

#include <vector>

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

        void AddPanel(IGUIPanel* panel);

    private:
        std::vector<IGUIPanel*> panels_;
    };
}
