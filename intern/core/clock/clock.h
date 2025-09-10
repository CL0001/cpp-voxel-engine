#pragma once

namespace VEng::Core
{
    class Clock
    {
    public:
        static Clock& Instance()
        {
            static Clock instance;
            return instance;
        }

        void Update();
        float GetDeltaTime() const;

    private:
        float deltaTime_;

        Clock() = default;
    };
}
