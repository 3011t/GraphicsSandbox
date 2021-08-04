#pragma once

#include "Camera.h"

struct InputEvents {
	float TimeDelta;
	MovementDirection MoveDirection;
	glm::vec2 MousePosDelta;
};