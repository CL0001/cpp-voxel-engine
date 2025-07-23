#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

class Shader
{
public:
	Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	void Use() const;

	unsigned int GetProgramId() const;

private:
	static std::string LoadShaderSource(const std::string& shader_path, const std::string& shader_tag);
	static unsigned int CompileShader(GLenum type, const std::string& source, const std::string& shader_tag);

	unsigned int program_id_;
};

#endif // SHADER_H
