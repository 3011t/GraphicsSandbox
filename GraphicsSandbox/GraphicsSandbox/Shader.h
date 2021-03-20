#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include<string>
#include<fstream>
#include<cstdio>
#include<unordered_map>

class Shader {
public:
	Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int32_t value);
private:
	uint32_t CompileShader(uint32_t type, const std::string& source);
	std::string GetShaderSource(const std::string& filename);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int32_t GetUniformLocation(const std::string& name);

	uint32_t m_RendererID;
	std::string m_VertexFilePath;
	std::string m_FragmentFilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
