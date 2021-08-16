#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(uint32_t shaderID, uint32_t bufferSize, const std::string& uniformBlockName)
  : m_RendererID(0),
	m_UniformBlockIndex(0),
	m_BufferSize(bufferSize)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
	glBufferData(GL_UNIFORM_BUFFER, m_BufferSize, nullptr, GL_STATIC_DRAW);

	m_UniformBlockIndex = glGetUniformBlockIndex(shaderID, uniformBlockName.c_str());
}

UniformBuffer::~UniformBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void UniformBuffer::Bind() const {
	glBindBufferBase(GL_UNIFORM_BUFFER, m_UniformBlockIndex, m_RendererID);
}

void UniformBuffer::Unbind() const {
	glBindBufferBase(GL_UNIFORM_BUFFER, m_UniformBlockIndex, 0);
}

void UniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset) {
	if (size + offset > m_BufferSize) printf("Warning! Overwriting data outside of buffer!");

	Bind();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}
