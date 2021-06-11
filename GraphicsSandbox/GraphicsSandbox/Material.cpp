#include "Material.h"

Material::Material() {
}

Material::Material(Shader* shader)
	: m_MaterialShader(shader), m_Flags(MaterialFlags::None)
{}

Material::~Material() {
	for (auto texture : m_Textures) delete(texture.second);
}

void Material::addTexture(const std::string & texName, TextureType texType) {
	uint32_t tempFlags = (uint32_t)m_Flags;
	Texture* tex = new Texture(texName);
	switch (texType) {
	case TextureType::Diffuse:
		m_Textures["u_Diffuse"] = tex;
		tempFlags |= (uint32_t)MaterialFlags::TexDiffuse;
		break;
	case TextureType::Specular:
		m_Textures["u_Specular"] = tex;
		tempFlags |= (uint32_t)MaterialFlags::TexSpecular;
		break;
	case TextureType::Normal:
		m_Textures["u_Normal"] = tex;
		tempFlags |= (uint32_t)MaterialFlags::TexNormal;
		break;
	case TextureType::Bump:
		m_Textures["u_Bump"] = tex;
		tempFlags |= (uint32_t)MaterialFlags::TexBump;
		break;
	case TextureType::Occlusion:
		m_Textures["u_Occlusion"] = tex;
		tempFlags |= (uint32_t)MaterialFlags::TexOcclusion;
		break;
	}
	m_Flags = (MaterialFlags)tempFlags;
}

void Material::setShader(const std::string& vertPath, const std::string& fragPath) {
}

void Material::setShader(Shader* shader) {
	m_MaterialShader = shader;
}

void Material::Bind() {
	m_MaterialShader->Bind();

	if ((uint32_t)MaterialFlags::TexDiffuse & (uint32_t)m_Flags) {
		m_Textures["u_Diffuse"]->Bind(0);
		m_MaterialShader->SetUniform1i("u_Diffuse", 0);
	}
	if ((uint32_t)MaterialFlags::TexSpecular & (uint32_t)m_Flags) {
		m_Textures["u_Specular"]->Bind(1);
		m_MaterialShader->SetUniform1i("u_Specular", 1);
	}
	if ((uint32_t)MaterialFlags::TexNormal & (uint32_t)m_Flags) {
		m_Textures["u_Normal"]->Bind(2);
		m_MaterialShader->SetUniform1i("u_Normal", 2);
	}
	if ((uint32_t)MaterialFlags::TexBump & (uint32_t)m_Flags) {
		m_Textures["u_Bump"]->Bind(3);
		m_MaterialShader->SetUniform1i("u_Bump", 3);
	}
	if ((uint32_t)MaterialFlags::TexOcclusion & (uint32_t)m_Flags) {
		m_Textures["u_Occlusion"]->Bind(4);
		m_MaterialShader->SetUniform1i("u_Occlusion", 4);
	}
}
