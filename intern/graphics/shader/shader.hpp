#pragma once

#include <filesystem>
#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace VEng::Graphics
{
	class Shader
	{
	public:
		Shader(const std::filesystem::path& vertex_shader_path,
			   const std::filesystem::path& fragment_shader_path);
		~Shader() noexcept;

		void Use() const noexcept;

		void SetUniform(const std::string& name, const glm::mat4& matrix) const noexcept;

		[[nodiscard]] unsigned int GetProgramId() const noexcept;

	private:
		static std::string LoadShaderSource(const std::string& shader_path);
		static unsigned int CompileShader(GLenum shader_type, const std::string& shader_source);
		static unsigned int CreateShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

		unsigned int program_id_;
	};
}
