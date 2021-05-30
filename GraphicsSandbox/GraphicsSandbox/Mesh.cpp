#include "Mesh.h"

Mesh::Mesh(VertexBuffer& vb, IndexBuffer& ib, VertexArray& va, VertexBufferLayout& bl)
 : m_VertexBuffer(vb), m_IndexBuffer(ib), m_VertexArray(va), m_VertBufferLayout(bl){}

void Mesh::Bind() const {
	m_VertexArray.Bind();
	m_VertexBuffer.Bind();
	m_IndexBuffer.Bind();
}

// Mesh Mesh::ReadFromFile(std::string filename) {}
