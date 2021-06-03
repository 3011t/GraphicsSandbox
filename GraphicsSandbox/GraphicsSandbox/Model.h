#pragma once

// stdlib includes
#include <string>
#include <vector>

// Local includes
#include "Mesh.h"
#include "Material.h"

class Model {
public:
	Model();

	static Model loadFromFile(const std::string& path);

	// TODO: Make it drawable by the renderer
private:


	std::vector<Mesh> m_Meshes;
	std::vector<Material> m_Materials;

	std::vector<Texture> loadMaterialTextures(); // TODO: Plug in tinyobjloader
};
