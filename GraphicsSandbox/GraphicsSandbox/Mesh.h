#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include <string>
#include <vector>

// Local includes
#include "Texture.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh {
public:
	Mesh(const std::vector<Vertex>& verts, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);

	void Bind() const;

	int32_t IndexCount() const { return m_IndexCount; }
private:
	std::vector<Texture> m_Textures;

	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;

	uint32_t m_IndexCount;
};

