#pragma once

// Library incudes
#include <glad/glad.h>

// Local includes
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mesh.h"

class Renderer {
public:
	Renderer();

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const Mesh& mesh, const Shader& shader) const;
	
	void SetClearColour(glm::vec4 rgba) { m_ClearColour = rgba; }
private:
	glm::vec4 m_ClearColour;
};

