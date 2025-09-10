#pragma once

#include <array>
#include <string>

#include "graphics/camera/camera.h"
#include "graphics/shader/shader.h"

namespace VEng::Graphics
{
    class Skybox
    {
    public:
        Skybox(const std::string& vertex_shader_path,
               const std::string& fragment_shader_path,
               unsigned int texture_unit,
               const std::array<std::string, 6>& faces);
        ~Skybox();

        void Draw(const VEng::Graphics::Camera& camera) const;

    private:
        Shader shader_;
        unsigned int texture_unit_;

        unsigned int vao_;
        unsigned int vbo_;
        unsigned int ebo_;
        unsigned int cubemap_texture_;

        static constexpr float vertices_[] =
        {
            // Coordinates
            -1.0f, -1.0f,  1.0f,  //        7--------6
             1.0f, -1.0f,  1.0f,  //       /|       /|
             1.0f, -1.0f, -1.0f,  //      4--------5 |
            -1.0f, -1.0f, -1.0f,  //      | |      | |
            -1.0f,  1.0f,  1.0f,  //      | 3------|-2
             1.0f,  1.0f,  1.0f,  //      |/       |/
             1.0f,  1.0f, -1.0f,  //      0--------1
            -1.0f,  1.0f, -1.0f
        };

        static constexpr unsigned int indices_[] =
        {
            // Right
            1, 2, 6,
            6, 5, 1,
            // Left
            0, 4, 7,
            7, 3, 0,
            // Top
            4, 5, 6,
            6, 7, 4,
            // Bottom
            0, 3, 2,
            2, 1, 0,
            // Back
            0, 1, 5,
            5, 4, 0,
            // Front
            3, 7, 6,
            6, 2, 3
        };
    };
}
