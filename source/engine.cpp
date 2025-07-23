#include "engine.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "spdlog/spdlog.h"
#include "glm/vec3.hpp"

#include "shader.h"

#include "cube.h"

Engine::Engine(const int width, const int height, const char* title)
{
    if (glfwInit() == 0)
        throw std::runtime_error("failed to initialize glfw");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window_ == nullptr)
        throw std::runtime_error("failed to initialize glfw");

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
        throw std::runtime_error("failed to initialize glfw");

    shader_.emplace(ASSETS_PATH "shaders/base_vertex.glsl", ASSETS_PATH "shaders/base_fragment.glsl");
    camera_.emplace(glm::vec3(0.0f, 0.0f, 0.0f), width, height);
}

Engine::~Engine()
{
    glfwTerminate();
}

void Engine::Run()
{
    const Cube cube;

    while (!glfwWindowShouldClose(window_))
    {
        camera_->HandleInput(window_, 0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_->Use();
        camera_->Matrix(45.0f, 0.1f, 100.0f, shader_->GetProgramId(), "camera_matrix");
        cube.Draw();


        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Engine::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    spdlog::info("Framebuffer size: {} x {}", width, height);
    glViewport(0, 0, width, height);
}