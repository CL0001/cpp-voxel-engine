#pragma once

namespace VEng::Core
{
    class Clock
    {
    public:
        Clock(const Clock&) = delete;
        Clock& operator=(const Clock&) = delete;

        static Clock& Instance()
        {
            static Clock instance;
            return instance;
        }

        void Update();

        [[nodiscard]] float GetDeltaTime() const noexcept;
        [[nodiscard]] float GetFrameRate() const noexcept;

    private:
        float delta_time_ = 0;

        Clock() noexcept = default;
    };
}
