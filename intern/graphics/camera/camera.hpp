#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

namespace VEng::Graphics
{
    struct CameraSettings
    {
        glm::vec3 position;
        glm::vec3 orientation;
        glm::vec3 up;
        int width;
        int height;
        float fov;
        float normal_speed;
        float accelerated_speed;
        float sensitivity;
    };

    class Camera
    {
    public:
        explicit Camera(const CameraSettings& settings);

        void UploadViewProjectionMatrix(unsigned int shader_program_id, const char* uniform) const noexcept;

        void HandleInput(GLFWwindow* window, double delta_time) noexcept;

        [[nodiscard]] glm::mat4 GetViewMatrix() const noexcept;
        [[nodiscard]] glm::mat4 GetViewMatrixNoTranslation() const noexcept;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const noexcept;

    private:
        glm::vec3 position_;
        glm::vec3 orientation_;
        glm::vec3 up_;

        int width_;
        int height_;
        float fov_;

        struct MovementSpeed
        {
            float normal;
            float accelerated;
            float current;
        } movement_speed_;

        float sensitivity_;
        bool first_mouse_click_;
    };
}
