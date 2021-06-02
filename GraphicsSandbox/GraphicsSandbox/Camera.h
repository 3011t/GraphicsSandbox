#pragma once

// Library includes
#include <glm/glm.hpp>

// stdlib includes
#include <cstdint>

enum class MovementDirection : uint32_t {
	None = 0x00000000,
	Forward = 0x00000001,
	Backward = 0x00000002,
	Left = 0x00000004,
	Right = 0x00000008,
	Up = 0x00000010,
	Down = 0x00000020,
};

class Camera {
public:
	Camera();

	void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
	void SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }
	void SetView(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up);
	const glm::mat4& GetView() const { return m_View; }
	const glm::mat4& GetInvView() const { return m_ViewInverse; }

	void SetProjection(float fov, float aspect, float near, float far);
	const glm::mat4& GetProjection() const { return m_Projection; }

	void Move(MovementDirection dir, const glm::vec2& mouseMove, float dt);

	//glm::mat4 CalculateMVP(glm::mat4 Model);
	const glm::vec4& GetCameraPosition() { return m_ViewInverse[3]; }
private:
	glm::mat4 m_View;
	glm::mat4 m_ViewInverse;
	glm::mat4 m_Projection;

	float m_MovementSpeed;
	float m_Sensitivity;
};
