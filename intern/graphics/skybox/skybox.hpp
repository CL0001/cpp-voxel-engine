#pragma once

#include <array>
#include <filesystem>

#include "graphics/renderer/renderer.hpp"
#include "graphics/shader/shader.hpp"

namespace VEng::Graphics
{
    struct SkyboxSettings
    {
        std::filesystem::path vertex_shader_path;
        std::filesystem::path fragment_shader_path;
        int texture_unit;
        std::array<std::filesystem::path, 6> cubemap_face_paths;
    };

    class Skybox final : public IRenderable
    {
    public:
        explicit Skybox(const SkyboxSettings& settings);
        ~Skybox() noexcept override;

        void Draw(const RenderContext& context) const noexcept override;

    private:
        Shader shader_;
        int texture_unit_;

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
            1, 2, 6, 6, 5, 1,  // Right
            0, 4, 7, 7, 3, 0,  // Left
            4, 5, 6, 6, 7, 4,  // Top
            0, 3, 2, 2, 1, 0,  // Bottom
            0, 1, 5, 5, 4, 0,  // Back
            3, 7, 6, 6, 2, 3   // Front
        };
    };
}
