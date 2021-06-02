#include "Model.h"

#include "tiny_gltf.h"

Model::Model()
{
}

// Prepared for ASCII glTF files.
Model Model::loadFromFile(const std::string& path)
{
	tinygltf::Model model;
	tinygltf::TinyGLTF gltf_ctx;
	std::string err;
	std::string warn;
	
	gltf_ctx.SetStoreOriginalJSONForExtrasAndExtensions(false);

	bool result = gltf_ctx.LoadASCIIFromFile(&model, &err, &warn, path);

	if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Err: %s\n", err.c_str());
	}

	return Model();
}
