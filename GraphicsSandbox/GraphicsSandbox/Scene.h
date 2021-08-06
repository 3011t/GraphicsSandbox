#pragma once

#include <vector>
#include <unordered_map>

#include "GLWrappers/VertexArray.h"
#include "GLWrappers/IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "InputEvents.h"

class Renderer;

// I am aware that my usage of pointers is ugly and I'm probably asking for trouble by using them,
// but I'm not sure how I'd go about copying the objects without f****** up the global GL state.

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh {
public:
	Mesh (const std::string& name, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	  : m_Name(name),
		m_VertexArray(),
		m_VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex)),
		m_IndexBuffer(&indices[0], indices.size())
	{
		m_BufferLayout.Push<float>(3);
		m_BufferLayout.Push<float>(3);
		m_BufferLayout.Push<float>(2);

		m_VertexArray.AddBuffer(m_VertexBuffer, m_BufferLayout);
	}

	void Bind() const {
		m_VertexArray.Bind();
		m_IndexBuffer.Bind();
	}

	uint32_t GetIndexCount() const {
		return m_IndexBuffer.GetCount();
	}

private:
	std::string m_Name;

	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;
	VertexBufferLayout m_BufferLayout;
	IndexBuffer m_IndexBuffer;

	friend Renderer;
};

struct Material {
	~Material() {
		delete(DiffuseMap);
	}

	std::string Name;

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;
	Texture* DiffuseMap;
};

struct Model {
	~Model() {
		for (auto mesh : Meshes) delete(mesh);
		for (auto material : Materials) delete(material);
	}

	std::string Name;
	std::vector<Mesh*> Meshes;
	std::vector<uint32_t> MeshMaterial;
	std::vector<Material*> Materials;
};

struct Instance {
	std::string ModelName;
	glm::mat4 Transform;
};

class Scene {
public:
	~Scene();

	void Update(const InputEvents& events);

	void AddModelFromFile(const std::string& filename, const std::string& modelName);
	void AddInstance(const Instance& instance);

	void AddCamera(const Camera& camera);
	void AddShader(const std::string& shaderName, const std::string& vertShaderFilename, const std::string& fragShaderFilename);
	void AddLight(const glm::vec3& position);

	void SetShader(const std::string& shaderName);
private:
	Shader* m_ActiveShader;

	std::vector<glm::vec3> m_Lights;
	Camera m_Camera;

	std::unordered_map<std::string, uint64_t> m_ShaderIndices;
	std::vector<Shader*> m_Shaders;

	std::unordered_map<std::string, uint64_t> m_ModelIndices;
	std::vector<Model*> m_Models;
	std::vector<Instance> m_ModelInstances;

	friend Renderer; // Yes, I'm letting Renderer touch the private parts of the Scene objects, it makes things easier. ;-)
};

