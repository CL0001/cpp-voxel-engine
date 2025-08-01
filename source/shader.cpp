#include "shader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "spdlog/spdlog.h"

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    const std::string vertex_shader_source = LoadShaderSource(vertex_shader_path);
    const std::string fragment_shader_source = LoadShaderSource(fragment_shader_path);

    const unsigned int vertex_shader_id = CompileShader(GL_VERTEX_SHADER, vertex_shader_source);
    const unsigned int fragment_shader_id = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

    program_id_ = CreateShaderProgram(vertex_shader_id, fragment_shader_id);
}

Shader::~Shader()
{
    glDeleteProgram(program_id_);
}

void Shader::Use() const
{
    glUseProgram(program_id_);
}

unsigned int Shader::GetProgramId() const
{
    return program_id_;
}

std::string Shader::LoadShaderSource(const std::string& shader_path)
{
    std::ifstream file(shader_path);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open shader source file: " + shader_path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    if (source.empty())
    {
        throw std::runtime_error("shader source is empty: " + shader_path);
    }

    return source;
}

unsigned int Shader::CompileShader(const GLenum shader_type, const std::string& shader_source)
{
    const unsigned int shader_id = glCreateShader(shader_type);
    const char* source = shader_source.c_str();

    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    GLint compile_success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_success);

    if (!compile_success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log);

        throw std::runtime_error("shader compilation failed: " + std::string(info_log));
    }

    return shader_id;
}

unsigned int Shader::CreateShaderProgram(const unsigned int vertex_shader_id, const unsigned int fragment_shader_id)
{
    const unsigned int shader_program_id = glCreateProgram();

    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);

    GLint link_success;
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &link_success);

    if (!link_success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program_id, 512, nullptr, info_log);

        throw std::runtime_error("shader program linking failed: " + std::string(info_log));
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return shader_program_id;
}
