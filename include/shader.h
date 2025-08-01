#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

class Shader
{
public:
	Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
	~Shader();

	void Use() const;

	unsigned int GetProgramId() const;

private:
	static std::string LoadShaderSource(const std::string& shader_path);
	static unsigned int CompileShader(GLenum shader_type, const std::string& shader_source);
	static unsigned int CreateShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

	unsigned int program_id_;
};

#endif // SHADER_H
