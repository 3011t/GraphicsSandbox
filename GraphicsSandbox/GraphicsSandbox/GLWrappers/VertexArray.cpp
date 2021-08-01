#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); ++i)
	{
		const VertexBufferElement& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
