#include "camera.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

Camera::Camera(const glm::vec3 position, const unsigned int width, const unsigned int height)
    : position_(position),
      orientation_(glm::vec3(0.0f, 0.0f, -1.0f)),
      up_(glm::vec3(0.0f, 1.0f, 0.0f)),
      width_(width),
      height_(height),
      speed_(0.1f),
      sensitivity_(50.0f),
      first_click_(false)
{
}

void Camera::Matrix(const float fov, const float near_plane, const float far_plane, unsigned int shader_program_id, const char* uniform) const
{
    const glm::mat4 view = glm::lookAt(position_, position_ + orientation_, up_);
    const glm::mat4 projection = glm::perspective(fov, static_cast<float>(width_) / static_cast<float>(height_), near_plane, far_plane);

    glUniformMatrix4fv(glGetUniformLocation(shader_program_id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

// TODO: Add delta_time to the engine and use it here.
void Camera::HandleInput(GLFWwindow* window, const double delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position_ += speed_ * orientation_ * static_cast<float>(delta_time);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position_ -= glm::normalize(glm::cross(orientation_, up_)) * speed_ * static_cast<float>(delta_time);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position_ -= speed_ * orientation_ * static_cast<float>(delta_time);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position_ += glm::normalize(glm::cross(orientation_, up_)) * speed_ * static_cast<float>(delta_time);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed_ = 1.0f;
    else
        speed_ = 0.4f;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (first_click_)
        {
            glfwSetCursorPos(window, width_ / 2.0, height_ / 2.0);
            first_click_ = false;
        }

        double mouse_x;
        double mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        const float rotate_x = sensitivity_ * static_cast<float>(mouse_y - height_ / 2.0) / static_cast<float>(height_);
        const float rotate_y = sensitivity_ * static_cast<float>(mouse_x - width_ / 2.0) / static_cast<float>(width_);

        const glm::vec3 new_orientation = glm::rotate(
            orientation_,
            glm::radians(-rotate_x),
            glm::normalize(glm::cross(orientation_, up_))
        );

        if (abs(glm::angle(new_orientation, up_) - glm::radians(90.0f)) <= glm::radians(85.0f))
            orientation_ = new_orientation;

        orientation_ = glm::rotate(orientation_, glm::radians(-rotate_y), up_);
        glfwSetCursorPos(window, width_ / 2, height_ / 2);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        first_click_ = true;
    }
}

