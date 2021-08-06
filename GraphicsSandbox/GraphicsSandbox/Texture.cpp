#include "Texture.h"

// For image loading
#include <stb_image.h>

Texture::Texture(const std::string& path)
  : m_RendererID(0),
	m_FilePath(path),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0),
	m_InitStatus(true)
{
	LoadFromFile();
}

Texture::~Texture() {
	if (m_InitStatus) glDeleteTextures(1, &m_RendererID);
}

void Texture::Init(const std::string& path) {
	m_FilePath = path;
	LoadFromFile();
	m_InitStatus = true;
}

void Texture::Reload() {
	LoadFromFile();
}

void Texture::UpdatePath(const std::string& path) {
	m_FilePath = path;
}

void Texture::Bind(uint32_t slot) const {
	if (!m_InitStatus) printf("This texture isn't initialized!");

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadFromFile() {
	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}
