#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// stdlib includes
#include <string>
#include <cstdint>

enum class TextureType {
	Diffuse,
	Specular,
	Normal,
	Occlusion,
	Bump,
};

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline int32_t GetWidth() { return m_Width; }
	inline int32_t GetHeight() { return m_Height; }
	inline int32_t GetBPP() { return m_BPP; }
private:
	uint32_t m_RendererID;
	std::string m_FilePath;
	uint8_t* m_LocalBuffer;
	int32_t m_Width, m_Height, m_BPP;
};

