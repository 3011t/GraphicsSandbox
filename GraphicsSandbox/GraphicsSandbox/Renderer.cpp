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

	glDrawElements(GL_TRIANGLES, mesh.IndexCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const Model& model) {
	auto meshes = model.getMeshes();
	auto materials = model.getMaterials();

	materials[0]->Bind();
	for (auto mesh : meshes) {
		mesh->Bind();
		glDrawElements(GL_TRIANGLES, mesh->IndexCount(), GL_UNSIGNED_INT, nullptr);
	}
}
