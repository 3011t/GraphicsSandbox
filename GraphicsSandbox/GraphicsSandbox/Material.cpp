#include "Material.h"

Material::Material() {
}

Material::Material(Shader* shader)
	: m_MaterialShader(shader), m_Diffuse(nullptr)
{}

Material::~Material() {
	delete(m_Diffuse);
}

void Material::addTexture(const std::string& texName) {
	m_Diffuse = new Texture(texName);
}

void Material::setShader(const std::string& vertPath, const std::string& fragPath) {
}

void Material::setShader(Shader* shader) {
	m_MaterialShader = shader;
}

void Material::Bind() {
	m_MaterialShader->Bind();

	if (m_Diffuse) m_Diffuse->Bind(0);
	m_MaterialShader->SetUniform1i("u_Diffuse", 0);
}

void Material::Unbind() {
	m_MaterialShader->Unbind();
	m_Diffuse->Unbind();
}
