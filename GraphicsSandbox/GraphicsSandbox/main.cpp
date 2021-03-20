// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Standard library includes
#include <cstdio>

// In-project includes
#include "Sandbox.h"

int main() {
    Sandbox box;

    if (!box.GetStatus()) {
        printf("Initialization failed.");
    }

    box.Run();

    return 0;
}