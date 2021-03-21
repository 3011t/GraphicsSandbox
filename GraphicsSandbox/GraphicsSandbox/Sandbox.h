#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// stdlib includes
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

// Local includes
//#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

class Sandbox {
public:
	Sandbox();
	~Sandbox();

	void Run();
	bool GetStatus() { return m_InitStatus; }
private:
	GLFWwindow* m_Window;
	bool m_InitStatus;
};