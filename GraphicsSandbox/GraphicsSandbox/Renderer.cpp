#include "Renderer.h"

Renderer::Renderer() : m_ClearColour(0.0f) {}

void Renderer::Clear() const {
	glClearColor(m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, m_ClearColour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	va.Bind();
	ib.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const Mesh& mesh, const Shader& shader) const {
	mesh.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(Scene& scene) const {
	// Bind shadow mapping shader
	
	// Create a FB for each lightsource

	// Calculate the shadow map for each lightsource

	// Cache the shadowmaps
	
	Shader* shader = scene.m_ActiveShader;
	
	shader->Bind();
	shader->SetUniformMat4f("u_Projection", scene.m_Camera.GetProjection());
	shader->SetUniformMat4f("u_View", scene.m_Camera.GetView());
	auto dir = scene.m_Camera.GetViewDirection();
	shader->SetUniform3f("u_ViewDir", dir.x, dir.y, dir.z);

	// Put all lights and shadowmaps into the shader via uniforms
	if (scene.m_ActiveShaderName == "Shadows") {
		shader->SetUniformBlockData("u_LightsBlock", &scene.m_Lights[0], scene.m_Lights.size() * sizeof(Light));
	}

	auto& instances = scene.m_ModelInstances;
	for (int i = 0; i < instances.size(); ++i) {
		shader->SetUniformMat4f("u_Model", instances[i].Transform);

		Model* model = scene.m_Models[scene.m_ModelIndices[instances[i].ModelName]];
		for (int i = 0; i < model->Meshes.size(); ++i) {
			Material* material = model->Materials[model->MeshMaterial[i]];
			shader->SetUniform3f("u_Ambient", material->Ambient.x, material->Ambient.y, material->Ambient.z);
			shader->SetUniform3f("u_Diffuse", material->Diffuse.x, material->Diffuse.y, material->Diffuse.z);
			shader->SetUniform3f("u_Specular", material->Specular.x, material->Specular.y, material->Specular.z);
			shader->SetUniform1f("u_Shininess", material->Shininess);
			if (material->DiffuseMap) {
				material->DiffuseMap->Bind(0);
				shader->SetUniform1i("u_DiffuseTexture", 0);
				shader->SetUniform1i("u_HasTexture", 1);
			}
			else {
				shader->SetUniform1i("u_HasTexture", 0);
			}

			model->Meshes[i]->Bind();
			glDrawElements(GL_TRIANGLES, model->Meshes[i]->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
