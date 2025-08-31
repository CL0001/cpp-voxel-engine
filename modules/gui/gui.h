#ifndef GUI_H
#define GUI_H

#include "glfw/glfw3.h"

class GUI
{
public:
    GUI(GLFWwindow* window);
    ~GUI();

    void Draw(float fps) const;
};

#endif // GUI_H
