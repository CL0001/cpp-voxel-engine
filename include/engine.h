#pragma once

#include <optional>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void Run() const;

private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* window_;
    std::optional<Shader> shader_;
};
