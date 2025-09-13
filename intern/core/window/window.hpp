#pragma once

#include <string_view>

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace VEng::Core
{
    struct WindowSettings
    {
        int width;
        int height;
        std::string_view title;
        bool enable_vsync;
    };

    class Window
    {
    public:
        explicit Window(const WindowSettings& settings);
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
