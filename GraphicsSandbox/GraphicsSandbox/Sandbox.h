#pragma once

// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <IL/il.h>

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

class Sandbox {
public:
	Sandbox();

	bool Init();
	void Run();
	void Uninit();
private:
	GLFWwindow* window;
};