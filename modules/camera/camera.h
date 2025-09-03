#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

class Camera
{
public:
    Camera(glm::vec3 position, unsigned int width, unsigned int height);

    void Matrix(float fov, float near_plane, float far_plane, unsigned int shader_program_id, const char* uniform) const;

    void HandleInput(GLFWwindow* window, double delta_time);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

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
