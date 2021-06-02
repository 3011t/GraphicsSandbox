#pragma once

// stdlib includes
#include <string>
#include <vector>

// Local includes
#include "Mesh.h"

class Model {
public:
	Model();

	static Model loadFromFile(const std::string& path);

	// TODO: Make it drawable by the renderer
private:

	std::vector<Mesh> m_Meshes;

	std::vector<Texture> loadMaterialTextures(); // TODO: Plug in tinyobjloader
};

