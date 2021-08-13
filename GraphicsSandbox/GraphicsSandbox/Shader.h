// The layout of this class is inspired by TheCherno's OpenGL tutorial series.
// I have added a few methods of my own(currently Reload() and SetLights()).

#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<unordered_map>

struct Light;

class Shader {
public:
	Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
	~Shader();

	void Reload();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform3f(const std::string& name, float f0, float f1, float f2);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int32_t value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	uint32_t SetLights(const std::vector<Light>& lights);
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
