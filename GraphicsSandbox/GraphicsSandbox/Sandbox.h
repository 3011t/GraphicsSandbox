#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// stdlib includes
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

// Local includes
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "Scene.h"

class Sandbox {
public:
	Sandbox();
	~Sandbox();

	void Run();
	bool GetStatus() { return m_InitStatus; }
private:
	InputEvents ProcessInput(float dt);

	GLFWwindow* m_Window;
	bool m_InitStatus;
	Camera m_Camera;
	double m_PrevMouseX;
	double m_PrevMouseY;
	bool m_DebugMousePosChanged;
};