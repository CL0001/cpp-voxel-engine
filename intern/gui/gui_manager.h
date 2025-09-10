#pragma once

#include <vector>
#include <memory>

#include "glfw/glfw3.h"

#include "igui_panel.h"

namespace VEng::GUI
{
    class Manager
    {
    public:
        explicit Manager(GLFWwindow* window);
        ~Manager();

        void Update(const std::vector<PanelData>& panel_data);
        void Draw() const;

        void AddPanel(std::unique_ptr<IGUIPanel> panel);

    private:
        std::vector<std::unique_ptr<IGUIPanel>> panels_;
    };
}
