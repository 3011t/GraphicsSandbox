#include "Material.h"

Material::Material(Shader& shader)
	: m_MaterialShader(shader)
{}

void Material::Bind() {
	m_MaterialShader.Bind();
}
