#ifndef CAMERA_H
#define CAMERA_H

#include "imgui_impl_glfw.h"
#include "glm/vec3.hpp"

#include "shader.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
    Camera(glm::vec3 position, int width, int height);

    void Matrix(float fov, float near_plane, float far_plane, unsigned int shader_program_id, const char* uniform) const;

    void HandleInput(GLFWwindow* window, float delta_time);

private:
    glm::vec3 position_;
    glm::vec3 orientation_;
    glm::vec3 up_;

    int width_;
    int height_;

    float speed_;
    float sensitivity_;

    bool first_click_;
};

#endif // CAMERA_H
