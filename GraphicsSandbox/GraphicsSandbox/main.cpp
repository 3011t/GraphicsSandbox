// Library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <IL/il.h>

// Standard library includes
#include <cstdio>

// In-project includes
#include "Sandbox.h"

int main() {
    Sandbox box;

    if (!box.Init()) {
        printf("Initialisation failed.");
    }

    box.Run();
    box.Uninit();

    return 0;
}