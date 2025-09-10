#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace VEng::Core
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        GLFWwindow* GetHandle() const;

        bool ShouldClose() const;
        void SwapBuffers() const;
        void PollEvents() const;

        static void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);

    private:
        GLFWwindow* window_;
    };
}
