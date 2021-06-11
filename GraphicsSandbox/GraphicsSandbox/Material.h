#pragma once

// Library includes
#include <glm/glm.hpp>

// stdlib includes
#include <string>
#include <unordered_map>

// Local includes
#include "Texture.h"
#include "Shader.h"

class Material {
public:
	Material();
	Material(Shader* shader);
	~Material();

	void addTexture(const std::string& texName, TextureType texType);
	void setShader(const std::string& vertPath, const std::string& fragPath);
	void setShader(Shader* shader);

	void Bind();
private:
	enum class MaterialFlags : uint32_t {
		None        = 0x0000,
		TexDiffuse  = 0x0001,
		TexNormal   = 0x0002,
		TexSpecular = 0x0004,
		TexBump     = 0x0008,
		TexOcclusion= 0x0010,
	};

	Shader* m_MaterialShader;
	std::unordered_map<std::string, Texture*> m_Textures;
	MaterialFlags m_Flags;
};

