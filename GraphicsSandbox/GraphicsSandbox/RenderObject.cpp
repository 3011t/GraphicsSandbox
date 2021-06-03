#include "RenderObject.h"

RenderObject::RenderObject(std::vector<Model> models) : m_Models(models), m_ObjectTransform(1.0f) {
	// Nothing yet
}

void RenderObject::Translate(const glm::vec3& translationVec) {
	m_ObjectTransform = glm::translate(m_ObjectTransform, translationVec);
}

void RenderObject::Scale(const glm::vec3& scaleVec) {
	m_ObjectTransform = glm::scale(m_ObjectTransform, scaleVec);
}

void RenderObject::Rotate(float angle, const glm::vec3& direction) {
	m_ObjectTransform = glm::rotate(m_ObjectTransform, angle, direction);
}
