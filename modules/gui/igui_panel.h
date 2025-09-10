#pragma once

#include <variant>

namespace VEng::GUI
{
    struct StatsData
    {
        float frame_rate;
        float memory_mb;
    };

    struct ControlsData
    {
        bool forward;
        bool backward;
        bool left;
        bool right;
        bool up;
        bool down;
        bool accelerate;
    };

    using PanelData = std::variant<StatsData, ControlsData>;

    class IGUIPanel
    {
    public:
        virtual ~IGUIPanel() = default;

        virtual void Update(const PanelData& data) = 0;
        virtual void Draw() const = 0;
    };
}
