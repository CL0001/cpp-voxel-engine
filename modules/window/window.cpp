#include "window.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "spdlog/spdlog.h"

Window::Window(const int width, const int height, const char* title)
    : window_(nullptr)
{
    if (glfwInit() == 0)
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window_ == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        spdlog::info("Framebuffer resized: {}x{}", w, h);
    });

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    spdlog::info("OpenGL loaded: {}.{}", GLVersion.major, GLVersion.minor);
}

Window::~Window()
{
    if (window_)
    {
        glfwDestroyWindow(window_);
    }

    glfwTerminate();
}

GLFWwindow* Window::GetHandle() const
{
    return window_;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(window_);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(window_);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::SetFramebufferSizeCallback(const GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), callback);
}

