#include "clock.h"

#include "glfw/glfw3.h"

void VEng::Core::Clock::Update()
{
    static double lastTime = glfwGetTime();
    const double currentTime = glfwGetTime();

    deltaTime_ = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
}

float VEng::Core::Clock::GetDeltaTime() const
{
    return deltaTime_;
}