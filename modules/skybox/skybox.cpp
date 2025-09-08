#include "skybox.h"

#include <stdexcept>

#include "glad/glad.h"
#include "stb_image.h"

#include "camera.h"
#include "shader.h"

Skybox::Skybox(const std::string& vertex_shader_path,
               const std::string& fragment_shader_path,
               const unsigned int texture_unit,
               const std::array<std::string, 6>& faces)
    : shader_(vertex_shader_path, fragment_shader_path),
      texture_unit_(texture_unit)
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenTextures(1, &cubemap_texture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture_);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < 6; ++i)
    {
        int width, height, nr_channels;

        if (unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nr_channels, 0))
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            throw std::runtime_error("Failed to load texture from file " + faces[i]);
        }
    }

    shader_.Use();
    glUniform1i(glGetUniformLocation(shader_.GetProgramId(), "skybox"), texture_unit_);
}

Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    glDeleteTextures(1, &cubemap_texture_);
}

void Skybox::Draw(const Camera& camera) const
{
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    shader_.Use();
    shader_.SetUniform("view", camera.GetViewMatrixNoTranslation());
    shader_.SetUniform("projection", camera.GetProjectionMatrix());

    glBindVertexArray(vao_);
    glActiveTexture(GL_TEXTURE0 + texture_unit_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture_);

    glDrawElements(GL_TRIANGLES, sizeof(indices_) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
}
