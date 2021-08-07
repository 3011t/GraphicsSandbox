#include "Scene.h"

#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"

#include <iostream>

Scene::~Scene() {
	for (auto shader : m_Shaders) delete(shader);
	for (auto model : m_Models) delete(model);
}

void Scene::Update(const InputEvents& events) {
	m_Camera.Move(events.MoveDirection, events.MousePosDelta, events.TimeDelta);
}

void Scene::AddInstance(const Instance& instance) {
	m_ModelInstances.push_back(instance);
}

void Scene::AddCamera(const Camera& camera) {
	m_Camera = camera;
}

void Scene::AddLight(const glm::vec3& position) {
}

void Scene::AddShader(const std::string& shaderName, const std::string& vertShaderFilename, const std::string& fragShaderFilename) {
	m_Shaders.push_back(new Shader(vertShaderFilename, fragShaderFilename));
	m_ShaderIndices[shaderName] = m_Shaders.size() - 1;
}

void Scene::ReloadShaders() {
	for (size_t i = 0; i < m_Shaders.size(); ++i) {
		m_Shaders[i]->Reload();
	}
}

void Scene::SetActiveShader(const std::string& shaderName) {
	m_ActiveShader = m_Shaders[m_ShaderIndices[shaderName]];
}


void Scene::AddModel(const std::string& modelName, const std::vector<Vertex>& vertices, const std::vector<uint32_t> indices, const std::string& texName) {
	Model* newModel = new Model();

	newModel->Meshes.push_back(new Mesh("", vertices, indices));
	newModel->Materials.push_back(new Material());
	newModel->Materials[0]->DiffuseMap = new Texture(texName);
	newModel->MeshMaterial.push_back(0);

	m_Models.push_back(newModel);
	m_ModelIndices[modelName] = m_Models.size() - 1;
}

// This Method is (hopefully) written in such a way as to minimize the amount of memory and draw calls that are
// necessary to draw the model. (Without using multiple texture units.)
void Scene::AddModelFromFile(const std::string& modelName, const std::string& filename) {
	//
	// Loader initialization
	//
	tinyobj::ObjReaderConfig readerConfig;
	const size_t lastSlash = filename.rfind('/');
	const std::string modelPath = filename.substr(0, lastSlash + 1);
	if (std::string::npos != lastSlash) readerConfig.mtl_search_path = modelPath;
	readerConfig.triangulate = true;
	tinyobj::ObjReader reader;

	//
	// Reading the .obj file, printing possible errors
	//
	if (!reader.ParseFromFile(filename, readerConfig) && !reader.Error().empty()) {
		std::cout << "TinyObjReader: " << reader.Error();
	}

	if (!reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	//
	// Parsing loaded data into a new Model
	//
	Model* newModel = new Model();
	newModel->Name = modelName;

	// Parse materials
	auto& materials = reader.GetMaterials();
	for (auto& material : materials) {
		Material* newMaterial = new Material();
		newMaterial->Name = material.name;

		// Get everything into local variables.
		// Probably not the most efficient way of doing this, but
		// it's worth it for avoiding long line lengths
		// and the optimizer will probably yeet them anyway.
		
		// All of these are 3 component vectors of real_t(float) type
		auto& ambient = material.ambient;
		auto& diffuse = material.diffuse;
		auto& specular = material.specular;
		float shininess = material.shininess;
		const std::string& diffuseTexname = material.diffuse_texname;

		newMaterial->Ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
		newMaterial->Diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
		newMaterial->Specular = glm::vec3(specular[0], specular[1], specular[2]);
		newMaterial->Shininess = shininess;
		newMaterial->DiffuseMap = new Texture(modelPath + diffuseTexname);

		newModel->Materials.push_back(newMaterial);
	}

	// Parse shapes/meshes
	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();

	std::vector<std::vector<Vertex>> newVerts(materials.size());
	std::vector<std::vector<uint32_t>> newIndices(materials.size());

	// Loop over shapes
	for (uint64_t shapeIndex = 0; shapeIndex < shapes.size(); ++shapeIndex) {
		uint64_t indexOffset = 0;

		// Loop over polygons(triangles)
		for (uint64_t faceIndex = 0; faceIndex < shapes[shapeIndex].mesh.num_face_vertices.size(); ++faceIndex) {

			// Loop over verts on polygons
			// This part creates massive memory overhead, because I'm duplicating vertices like crazy, TODO
			uint64_t faceVertices = shapes[shapeIndex].mesh.num_face_vertices[faceIndex];
			for (uint64_t v = 0; v < faceVertices; ++v) {

				uint32_t materialID = shapes[shapeIndex].mesh.material_ids[faceIndex];
				tinyobj::index_t vertIndex = shapes[shapeIndex].mesh.indices[indexOffset + v];

				// Create and save the new vertex
				glm::vec3 position(0.0f);
				glm::vec3 normal(0.0f);
				glm::vec2 texCoords(0.0f);

				position.x = attrib.vertices[3 * size_t(vertIndex.vertex_index) + 0];
				position.y = attrib.vertices[3 * size_t(vertIndex.vertex_index) + 1];
				position.z = attrib.vertices[3 * size_t(vertIndex.vertex_index) + 2];

				if (vertIndex.normal_index >= 0) {
					normal.x = attrib.normals[3 * size_t(vertIndex.normal_index) + 0];
					normal.y = attrib.normals[3 * size_t(vertIndex.normal_index) + 1];
					normal.z = attrib.normals[3 * size_t(vertIndex.normal_index) + 2];
				}

				if (vertIndex.texcoord_index >= 0) {
					texCoords.s = attrib.texcoords[2 * size_t(vertIndex.texcoord_index) + 0];
					texCoords.t = attrib.texcoords[2 * size_t(vertIndex.texcoord_index) + 1];
				}

				Vertex newVertex = { position, normal, texCoords };
				newVerts[materialID].push_back(newVertex);
				newIndices[materialID].push_back(newVerts[materialID].size() - 1);
			}

			indexOffset += faceVertices;
		}
	}

	for (int i = 0; i < materials.size(); ++i) {
		newModel->Meshes.push_back(new Mesh("", newVerts[i], newIndices[i]));
		newModel->MeshMaterial.push_back(i);
	}

	m_Models.push_back(newModel);
	m_ModelIndices[modelName] = m_Models.size() - 1;
}
