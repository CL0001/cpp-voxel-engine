#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace VEng::Core
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window() noexcept;

        [[nodiscard]] GLFWwindow* GetHandle() const noexcept;
        [[nodiscard]] bool ShouldClose() const noexcept;

        void SwapBuffers() const noexcept;
        void PollEvents() const noexcept;

        static void SetFramebufferSizeCallback(GLFWframebuffersizefun callback) noexcept;

    private:
        GLFWwindow* window_;
    };
}
