#pragma once

// Library incudes
#include <glad/glad.h>

// Local includes
#include "Shader.h"
#include "Scene.h"

class Renderer {
public:
	Renderer();

	void Clear() const;

	// Draw functions
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const Scene& scene) const;

	void SetClearColour(glm::vec4 rgba) { m_ClearColour = rgba; }
private:
	glm::vec4 m_ClearColour;
};

