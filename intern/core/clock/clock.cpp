#include "clock.hpp"

#include "glfw/glfw3.h"

void VEng::Core::Clock::Update()
{
    static double lastTime = glfwGetTime();
    const double currentTime = glfwGetTime();

    delta_time_ = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
}

float VEng::Core::Clock::GetDeltaTime() const noexcept
{
    return delta_time_;
}

float VEng::Core::Clock::GetFrameRate() const noexcept
{
    return delta_time_ > 0 ? 1.0f / delta_time_ : 0.0f;
}
