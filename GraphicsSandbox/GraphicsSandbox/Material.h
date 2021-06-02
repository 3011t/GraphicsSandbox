#pragma once

// Library includes
#include <glm/glm.hpp>

// stdlib includes
#include <string>

// Local includes
#include "Texture.h"

class Material {
public:
	Material(const std::string& specularTexPath, const std::string& diffuseTexPath);

	void Bind();
private:
	Texture m_Specular;
	Texture m_Diffuse;
	glm::vec4 m_BaseColour;
};

