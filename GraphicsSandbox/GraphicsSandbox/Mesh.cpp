#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<uint32_t>& indices)
  : m_VertexBuffer(&verts[0], verts.size() * sizeof(Vertex)),
	m_VertexArray(),
	m_IndexBuffer(&indices[0], indices.size() * sizeof(uint32_t)),
	m_IndexCount(indices.size())
{

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position
	layout.Push<float>(3); // Normal
	layout.Push<float>(2); // Tex Coords

	m_VertexArray.AddBuffer(m_VertexBuffer, layout);
}

void Mesh::Bind() const {
	m_VertexArray.Bind();
	m_IndexBuffer.Bind();

	// TODO: Tell Shader Uniforms to use specular/diffuse textures
}
