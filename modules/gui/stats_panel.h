#pragma once

#include "igui_panel.h"

namespace VEng::GUI
{
    class StatsPanel final : public IGUIPanel
    {
    public:
        StatsPanel() = default;

        void Update(const PanelData& data) override;
        void Draw() const override;

    private:
        StatsData stats_data_{};
    };
}
