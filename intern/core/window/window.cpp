#include "window.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "spdlog/spdlog.h"

VEng::Core::Window::Window(const int width, const int height, const char* title)
    : window_(nullptr)
{
    if (glfwInit() == 0)
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window_ == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);

        spdlog::info("Framebuffer resized: {}x{}", w, h);
    });

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    spdlog::info("OpenGL loaded: {}.{}", GLVersion.major, GLVersion.minor);
}

VEng::Core::Window::~Window() noexcept
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

GLFWwindow* VEng::Core::Window::GetHandle() const noexcept
{
    return window_;
}

bool VEng::Core::Window::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(window_);
}

void VEng::Core::Window::SwapBuffers() const noexcept
{
    glfwSwapBuffers(window_);
}

void VEng::Core::Window::PollEvents() const noexcept
{
    glfwPollEvents();
}

void VEng::Core::Window::SetFramebufferSizeCallback(const GLFWframebuffersizefun callback) noexcept
{
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), callback);
}
