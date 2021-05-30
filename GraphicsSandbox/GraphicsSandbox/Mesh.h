#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include <string>
#include <fstream>

// Local includes
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Mesh {
public:
	Mesh(VertexBuffer& vb, IndexBuffer& ib, VertexArray& va, VertexBufferLayout& bl);

	void Bind() const;

	int32_t GetIndexCount() const { return m_IndexBuffer.GetCount(); }

	const VertexArray& GetVertexArray() const { return m_VertexArray; }
	const VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }
	const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; }

	// static Mesh ReadFromFile(std::string filename);
private:
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	VertexArray m_VertexArray;
	VertexBufferLayout m_VertBufferLayout;
};

