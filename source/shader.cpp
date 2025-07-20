#include "shader.h"

#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "spdlog/spdlog.h"

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    const std::string vertex_source = LoadShaderSource(vertex_shader_path, "VERTEX_SHADER");
    const std::string fragment_source = LoadShaderSource(fragment_shader_path, "FRAGMENT_SHADER");

    const unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_source, "VERTEX");
    const unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_source, "FRAGMENT");

    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader);
    glAttachShader(program_id_, fragment_shader);
    glLinkProgram(program_id_);

    GLint link_success;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &link_success);
    if (!link_success)
    {
        char info_log[512];
        glGetProgramInfoLog(program_id_, 512, nullptr, info_log);
        spdlog::error("shader program linking failed: {}", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Use() const
{
    glUseProgram(program_id_);
}

unsigned int Shader::GetProgramId() const
{
    return program_id_;
}

std::string Shader::LoadShaderSource(const std::string& shader_path, const std::string& shader_tag)
{
    std::ifstream file(shader_path);
    if (!file.is_open())
    {
        spdlog::error("[{}] cannot open shader source file: {}", shader_tag, shader_path);

        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    if (source.empty())
        spdlog::error("[{}] shader source is empty: {}", shader_tag, shader_path);

    return source;
}

unsigned int Shader::CompileShader(GLenum type, const std::string& source, const std::string& shader_tag)
{
    const unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        spdlog::error("[{}] cannot compile shader: {}", shader_tag, source);
    }

    return shader;
}
