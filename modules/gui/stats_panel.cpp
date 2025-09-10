#include "stats_panel.h"

#include "imgui.h"

void VEng::GUI::StatsPanel::Update(const PanelData& data)
{
    if (std::holds_alternative<StatsData>(data))
    {
        stats_data_ = std::get<StatsData>(data);
    }
}

void VEng::GUI::StatsPanel::Draw() const
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(350, 150), ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(0.8f);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize;

    ImGui::Begin("Stats", nullptr, window_flags);

    ImGui::SetWindowFontScale(2.0f);
    ImGui::Text("FPS: %.1f", stats_data_.frame_rate);
    ImGui::Text("Memory: %.1f MB", stats_data_.memory_mb);

    ImGui::End();
}
