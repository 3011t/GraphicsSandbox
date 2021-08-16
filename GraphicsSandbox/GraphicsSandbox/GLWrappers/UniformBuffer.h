#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include <cstdint>
#include <string>
#include <cstdio>

class UniformBuffer {
public:
	UniformBuffer(uint32_t shaderID, uint32_t bufferSize, const std::string& uniformBlockName);
	~UniformBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, uint32_t size, uint32_t offset = 0);
private:
	uint32_t m_RendererID;
	uint32_t m_UniformBlockIndex;
	uint32_t m_BufferSize;
};

