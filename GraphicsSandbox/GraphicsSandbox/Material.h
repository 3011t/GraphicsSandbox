#pragma once

// Library includes
#include <glm/glm.hpp>

// stdlib includes
#include <string>
#include <unordered_map>

// Local includes
#include "Texture.h"
#include "Shader.h"

// TODO: This class should get an extreme simplification, no texture clusterfuck mess

class Material {
public:
	Material();
	Material(Shader* shader);
	~Material();

	void addTexture(const std::string& texName);
	void setShader(const std::string& vertPath, const std::string& fragPath);
	void setShader(Shader* shader);

	void Bind();
	void Unbind();
private:
	Shader* m_MaterialShader;
	Texture* m_Diffuse;
};

