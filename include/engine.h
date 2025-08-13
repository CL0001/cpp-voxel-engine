#ifndef ENGINE_H
#define ENGINE_H

#include <optional>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader.h"
#include "camera.h"
#include "world.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void Run();

private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static double CalculateDeltaTime();

    GLFWwindow* window_;
    std::optional<Shader> shader_;
    std::optional<Camera> camera_;
    std::optional<World> world_;
};

#endif // ENGINE_H
