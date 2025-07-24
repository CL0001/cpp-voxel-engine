#ifndef CAMERA_H
#define CAMERA_H

#include "imgui_impl_glfw.h"
#include "glm/vec3.hpp"

#include "shader.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
    Camera(glm::vec3 position, unsigned int width, unsigned int height);

    void Matrix(float fov, float near_plane, float far_plane, unsigned int shader_program_id, const char* uniform) const;

    void HandleInput(GLFWwindow* window, double delta_time);

private:
    glm::vec3 position_;
    glm::vec3 orientation_;
    glm::vec3 up_;

    unsigned int width_;
    unsigned int height_;

    float speed_;
    float sensitivity_;

    bool first_click_;
};

#endif // CAMERA_H
