#pragma once

#include <vector>
#include <unordered_map>

#include "GLWrappers/VertexArray.h"
#include "GLWrappers/IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

class Renderer;

// TODO:
// Separate static and dynamic geometry

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Mesh {
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;
};

struct Material {
	Texture Diffuse;
};

struct Model {
	std::string Name;
	Mesh Mesh;
	Material Material;
};

struct ModelInstance {
	std::string ModelName;
	glm::mat4 Transform;
};

class Scene {
public:

	void Update();

	void AddModel(Model model);

	// Static models
	void AddStaticModelInstance(ModelInstance instance);
	void FinalizeStaticGeometry();

	void AddCamera(Camera camera);
	void AddShader(Shader shader);
	void AddLight(const glm::vec3& position);
private:
	uint64_t m_currentShader;

	std::vector<glm::vec3> m_Lights;
	Camera m_Camera;
	std::vector<Shader> m_Shaders;

	std::unordered_map<std::string, uint64_t> m_ModelIndices;
	std::vector<Model> m_Models;
	std::vector<ModelInstance> m_StaticModelInstances;

	std::unordered_map<std::string, uint64_t> m_StaticGeometryIndices;
	std::vector<Material> m_StaticMaterials;
	std::vector<VertexArray> m_VertexArrays;
	std::vector<IndexBuffer> m_IndexBuffers;

	friend Renderer;
};

