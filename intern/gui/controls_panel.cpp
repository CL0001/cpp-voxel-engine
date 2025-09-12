#include "controls_panel.hpp"

#include "imgui.h"

void VEng::GUI::ControlsPanel::Update(const PanelData& data)
{
    if (std::holds_alternative<ControlsData>(data))
    {
        controls_data_ = std::get<ControlsData>(data);
    }
}

void VEng::GUI::ControlsPanel::Draw() const
{
    ImGui::SetNextWindowPos(ImVec2(10, 200), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(350, 350), ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(0.8f);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize;
    ImGui::Begin("Controls", nullptr, window_flags);

    ImGui::SetWindowFontScale(2.0f);

    constexpr float key_small = 60.0f;
    constexpr float key_medium = key_small * 2.0f;
    constexpr float key_large = key_small * 3.0f;

    auto DrawKey = [](const char* key, const bool pressed, const ImVec2& size = ImVec2(60, 60))
    {
        const ImVec4 color = pressed ? ImVec4(0.2f, 0.7f, 0.2f, 1.0f) : ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::Button(key, size);
        ImGui::PopStyleColor();
    };

    ImGui::Dummy(ImVec2(key_medium + key_small + 8, 0));
    ImGui::SameLine();
    DrawKey("W", controls_data_.forward, ImVec2(key_small, 60));
    ImGui::NewLine();

    DrawKey("Shift", controls_data_.down, ImVec2(key_medium, 60));
    ImGui::SameLine();
    DrawKey("A", controls_data_.left, ImVec2(key_small, 60));
    ImGui::SameLine();
    DrawKey("S", controls_data_.backward, ImVec2(key_small, 60));
    ImGui::SameLine();
    DrawKey("D", controls_data_.right, ImVec2(key_small, 60));
    ImGui::NewLine();

    DrawKey("Ctrl", controls_data_.accelerate, ImVec2(key_medium, 60));
    ImGui::SameLine();
    DrawKey("Space", controls_data_.up, ImVec2(key_large + 16, 60));
    ImGui::NewLine();

    ImGui::End();
}
