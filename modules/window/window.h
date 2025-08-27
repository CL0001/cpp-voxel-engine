#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "glfw/glfw3.h"

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

#endif // WINDOW_H
