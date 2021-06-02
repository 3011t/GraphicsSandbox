#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_View(1.0f), m_ViewInverse(1.0f), m_MovementSpeed(5.0f), m_Sensitivity(0.1f) {}

void Camera::SetView(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up) {
	m_View = glm::lookAt(eye, lookAt, up);
	m_ViewInverse = glm::inverse(m_View);
}

void Camera::SetProjection(float fov, float aspect, float near, float far) {
	m_Projection = glm::perspective(fov, aspect, near, far);
}

void Camera::Move(MovementDirection direction, const glm::vec2& mouseMove, float dt) {
	glm::mat4 view(m_ViewInverse[0], m_ViewInverse[1], m_ViewInverse[2], glm::vec4(0.0f));
	glm::vec4& aside = view[0];
	glm::vec4& up = view[1];
	glm::vec4& dir = view[2];

	// Update camera orientation
	float yaw = atan2(dir.z, dir.x);
	float pitch = asin(dir.y);

	yaw -= mouseMove.x * m_Sensitivity * dt;
	pitch -= mouseMove.y * m_Sensitivity * dt;

	dir.x = cos(pitch) * cos(yaw);
	dir.y = sin(pitch);
	dir.z = cos(pitch) * sin(yaw);
	dir = glm::vec4(glm::normalize(glm::vec3(dir)), 0.0f);

	// Update camera position
	glm::vec4& position = view[3];
	position = m_ViewInverse[3];
	if ((int)direction & (int)MovementDirection::Forward)
		position -= dir * m_MovementSpeed * dt;

	if ((int)direction & (int)MovementDirection::Backward)
		position += dir * m_MovementSpeed * dt;

	if ((int)direction & (int)MovementDirection::Left)
		position -= aside * m_MovementSpeed * dt;

	if ((int)direction & (int)MovementDirection::Right)
		position += aside * m_MovementSpeed * dt;

	if ((int)direction & (int)MovementDirection::Up)
		position += up * m_MovementSpeed * dt;

	if ((int)direction & (int)MovementDirection::Down)
		position -= up * m_MovementSpeed * dt;

	m_ViewInverse[0] = glm::vec4(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(dir))), 0.0f);
	m_ViewInverse[1] = glm::vec4(glm::normalize(glm::cross(glm::vec3(dir), glm::vec3(m_ViewInverse[0]))), 0.0f);
	m_ViewInverse[2] = glm::vec4(glm::normalize(glm::vec3(dir)), 0.0f);
	m_ViewInverse[3] = position;
	m_View = glm::inverse(m_ViewInverse);
}

/*
glm::mat4 Camera::CalculateMVP(glm::mat4 Model)
{
	return m_Projection * m_View * Model;
}
*/
