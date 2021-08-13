// This file is inspired by TheCherno's OpenGL tutorial series.

#pragma once

// Library includes
#include <glad/glad.h>

// stdlib includes
#include <vector>

struct VertexBufferElement {
	uint32_t type;
	uint32_t count;
	uint32_t normalized;

	static uint32_t GetSizeOfType(uint32_t type) {
		switch (type) {
			case GL_FLOAT:        return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
		}
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(uint32_t count) {
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<uint32_t>(uint32_t count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline uint32_t GetStride() const { return m_Stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
};

