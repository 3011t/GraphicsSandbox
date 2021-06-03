#pragma once

// Library includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Local includes
#include "Model.h"

// This class will serve as the main type of target for rendering.
// It is done so that I can have multiple instances of a model on screen,
// while every object is neatly packed inside its own class instance.

class RenderObject {
public:
	RenderObject(std::vector<Model> models);

	void Translate(const glm::vec3& translationVec);
	void Scale(const glm::vec3& scaleVec);
	void Rotate(float angle, const glm::vec3& direction);
private:
	std::vector<Model> m_Models;
	glm::mat4 m_ObjectTransform;
};

