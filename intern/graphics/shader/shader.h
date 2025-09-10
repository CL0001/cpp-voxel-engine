#pragma once

#include <string>

#include "glad/glad.h"
#include "glm/matrix.hpp"

namespace VEng::Graphics
{
	class Shader
	{
	public:
		Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
		~Shader();

		void Use() const;

		void SetUniform(const std::string& name, const glm::mat4& matrix) const;

		unsigned int GetProgramId() const;

	private:
		static std::string LoadShaderSource(const std::string& shader_path);
		static unsigned int CompileShader(GLenum shader_type, const std::string& shader_source);
		static unsigned int CreateShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

		unsigned int program_id_;
	};
}
