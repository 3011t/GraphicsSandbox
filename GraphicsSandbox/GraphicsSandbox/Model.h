#pragma once

// stdlib includes
#include <string>
#include <vector>

// Local includes
#include "Mesh.h"
#include "Material.h"

class Model {
public:
	Model(const std::vector<Mesh*>& meshes, const std::vector<Material*>& materials, const std::vector<uint64_t>& meshMaterialIndices);
	~Model();

	void addMaterial(Material* material);
	void setCommonShader(Shader* shader);

	const std::vector<Mesh*>& getMeshes() const { return m_Meshes; }
	const std::vector<Material*>& getMaterials() const { return m_Materials; }
	const std::vector<uint64_t>& getMaterialIndices() const { return m_meshMaterialIndices; }

	static Model loadFromFile(const std::string& path);
private:
	std::vector<Mesh*> m_Meshes;
	std::vector<Material*> m_Materials;
	std::vector<uint64_t> m_meshMaterialIndices;
};
