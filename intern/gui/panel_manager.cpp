#include "panel_manager.hpp"

#include <stdexcept>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "igui_panel.hpp"

VEng::GUI::PanelManager::PanelManager(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

VEng::GUI::PanelManager::~PanelManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void VEng::GUI::PanelManager::Update(const std::vector<PanelData>& panel_data)
{
    if (panel_data.size() != panels_.size())
    {
        throw std::runtime_error("PanelData size does not match number of registered panels!");
    }

    for (size_t i = 0; i < panels_.size(); ++i)
    {
        panels_[i]->Update(panel_data[i]);
    }
}

void VEng::GUI::PanelManager::Draw(const Graphics::RenderContext& context) const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (const auto& panel : panels_)
    {
        panel->Draw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
