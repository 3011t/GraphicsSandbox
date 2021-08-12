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
	Camera(const Camera& other);

	void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
	void SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }
	void SetView(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up);
	void SetPosition(const glm::vec3 & pos);

	const glm::vec4& GetPosition() { return m_ViewInverse[3]; }
	const glm::mat4& GetView() const { return m_View; }
	const glm::mat4& GetInvView() const { return m_ViewInverse; }
	const glm::vec4& GetViewDirection() const { return m_View[2]; }

	void SetProjection(float fov, float aspect, float near, float far);
	const glm::mat4& GetProjection() const { return m_Projection; }

	void Move(MovementDirection dir, const glm::vec2& mouseMove, float dt);
private:
	glm::mat4 m_View;
	glm::mat4 m_ViewInverse;
	glm::mat4 m_Projection;

	float m_MovementSpeed;
	float m_Sensitivity;
};
