#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <IL/il.h>

class Sandbox {
public:
	Sandbox();

	bool Init();
	void Run();
	void Uninit();
private:
	GLFWwindow* window;
};