#pragma once

#include "igui_panel.h"

namespace VEng::GUI
{
    class ControlsPanel final : public IGUIPanel
    {
    public:
        ControlsPanel() = default;

        void Update(const PanelData& data) override;
        void Draw() const override;

    private:
        ControlsData controls_data_{};
    };
}
