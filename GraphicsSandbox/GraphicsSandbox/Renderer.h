#pragma once

// Library incudes
#include <glad/glad.h>

// Local includes
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer {
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:
};

