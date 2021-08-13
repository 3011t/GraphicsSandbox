// This file is inspired by TheCherno's OpenGL tutorial series.

#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// stdlib includes
#include <string>
#include <cstdint>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void Init(const std::string& path);
	void Reload();
	void UpdatePath(const std::string& path);

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline int32_t GetWidth() { return m_Width; }
	inline int32_t GetHeight() { return m_Height; }
	inline int32_t GetBPP() { return m_BPP; }
private:
	inline void LoadFromFile();

	uint32_t m_RendererID;
	std::string m_FilePath;
	uint8_t* m_LocalBuffer;
	int32_t m_Width, m_Height, m_BPP;
};
