#pragma once

// Library includes
#include <glm/glm.hpp>

// stdlib includes
#include <string>

// Local includes
#include "Texture.h"
#include "Shader.h"

class Material {
public:
	Material(const std::string& specularTexPath, const std::string& diffuseTexPath);

	void Bind();
private:
	Shader m_MaterialShader;

	Texture m_Albedo;
	Texture m_Specular;
	Texture m_Diffuse;
	Texture m_Normal;
	Texture m_Occlusion;
	Texture m_Metallic;
};

