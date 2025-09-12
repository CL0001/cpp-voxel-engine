#include "camera.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/io.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "spdlog/fmt/bundled/base.h"

VEng::Graphics::Camera::Camera(const CameraSettings& settings)
    : position_(settings.position),
      orientation_(settings.orientation),
      up_(settings.up),
      width_(settings.width),
      height_(settings.height),
      fov_(settings.fov),
      movement_speed_(settings.normal_speed, settings.accelerated_speed, settings.normal_speed),
      sensitivity_(settings.sensitivity),
      first_mouse_click_(false)
{
}

void VEng::Graphics::Camera::UploadViewProjectionMatrix(const unsigned int shader_program_id, const char* uniform) const noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program_id, uniform), 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix() * GetViewMatrix()));
}

void VEng::Graphics::Camera::HandleInput(GLFWwindow* window, const double delta_time) noexcept
{
    const float velocity = movement_speed_.current * static_cast<float>(delta_time);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position_ += orientation_ * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position_ -= orientation_ * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position_ -= glm::normalize(glm::cross(orientation_, up_)) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position_ += glm::normalize(glm::cross(orientation_, up_)) * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position_ += up_ * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        position_ -= up_ * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        movement_speed_.current = movement_speed_.accelerated;
    }
    else
    {
        movement_speed_.current = movement_speed_.normal;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (first_mouse_click_)
        {
            glfwSetCursorPos(window, width_ / 2.0, height_ / 2.0);
            first_mouse_click_ = false;
        }

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        const float rotate_x = sensitivity_ * static_cast<float>(mouse_y - height_ / 2.0) / static_cast<float>(height_);
        const float rotate_y = sensitivity_ * static_cast<float>(mouse_x - width_ / 2.0) / static_cast<float>(width_);

        const glm::vec3 new_orientation = glm::rotate(
            orientation_,
            glm::radians(-rotate_x),
            glm::normalize(glm::cross(orientation_, up_))
        );

        if (abs(glm::angle(new_orientation, up_) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            orientation_ = new_orientation;
        }

        orientation_ = glm::rotate(orientation_, glm::radians(-rotate_y), up_);
        glfwSetCursorPos(window, width_ / 2.0, height_ / 2.0);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        first_mouse_click_ = true;
    }
}

glm::mat4 VEng::Graphics::Camera::GetViewMatrix() const noexcept
{
    return glm::lookAt(position_, position_ + orientation_, up_);
}

glm::mat4 VEng::Graphics::Camera::GetViewMatrixNoTranslation() const noexcept
{
    return glm::mat3(glm::lookAt(position_, position_ + orientation_, up_));
}

glm::mat4 VEng::Graphics::Camera::GetProjectionMatrix() const noexcept
{
    return glm::perspective(glm::radians(fov_), static_cast<float>(width_) / static_cast<float>(height_), 0.1f, 1000.0f);
}
