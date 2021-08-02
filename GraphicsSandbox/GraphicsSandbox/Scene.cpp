#include "Scene.h"

void Scene::Update() {
}

void Scene::AddModel(Model model) {
	m_Models.push_back(model);
	m_ModelIndices[model.Name] = m_Models.size() - 1;
}

void Scene::AddStaticModelInstance(ModelInstance instance) {
	m_StaticModelInstances.push_back(instance);
}

void Scene::FinalizeStaticGeometry() {
	
}

void Scene::AddCamera(Camera camera) {
	m_Camera = camera;
}

void Scene::AddShader(Shader shader) {
	m_Shaders.push_back(shader);
	m_currentShader = m_Shaders.size() - 1;
}

void Scene::AddLight(const glm::vec3& position) {
}
