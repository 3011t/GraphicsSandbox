#include "Sandbox.h"

// My naming convention with these function is terrible
// TODO: Fix
void glfwErrorCallback(int error, const char* description)
{
    printf("GLFW Error %i: %s\n", error, description);
}

void glfwFramebufferCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static bool vsync = false;
    // Notify the window that user wants to exit the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Enable/disable MSAA - note that it still uses the MSAA buffer
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        if (glIsEnabled(GL_MULTISAMPLE))
            glDisable(GL_MULTISAMPLE);
        else
            glEnable(GL_MULTISAMPLE);
    }

    // Enable/disable wireframe rendering
    if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
    {
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if (polygonMode[0] == GL_FILL)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Enable/disable backface culling
    if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
    {
        if (glIsEnabled(GL_CULL_FACE))
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }

    // Enable/disable depth test
    if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
    {
        if (glIsEnabled(GL_DEPTH_TEST))
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);
    }

    // Enable/disable vsync
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
    {
        vsync = !vsync;
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }
}

void GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    printf("Type[0x%x], Severity[0x%x], %s\n", type, severity, message);
}

Sandbox::Sandbox() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        m_InitStatus = false;
        return;
    }
    m_Window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        m_InitStatus = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize OpenGL context
    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGL()) {
        glfwTerminate();
        m_InitStatus = false;
    }

    // Automatically adjust GL viewport !! TODO: get new resolution to change projection so it doesn't look weird
    glfwSetFramebufferSizeCallback(m_Window, glfwFramebufferCallback);

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Make OpenGL print debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);
    // Enable texture blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_Camera.SetProjection(glm::radians(70.0f), (16.0f / 9.0f), 0.1f, 1000.0f);
    m_Camera.SetView(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //m_Camera.SetMovementSpeed(1.0f);
    m_Camera.SetSensitivity(0.01f);

    glfwGetCursorPos(m_Window, &m_PrevMouseX, &m_PrevMouseY);

    m_InitStatus = true;
}

Sandbox::~Sandbox() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Sandbox::Run() {

    float positionsCube[] = {
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    };

    uint32_t indicesCube[] = {
        2, 0, 1,
        2, 1, 3,
        4, 5, 6,
        5, 7, 6,
        4, 5, 0,
        5, 1, 0,
        1, 5, 3,
        5, 7, 3,
        6, 7, 2,
        7, 3, 2,
        4, 0, 6,
        0, 2, 6
    };

    float positionsFloor[] = {
        -2.0f,  0.0f,  2.0f,
        -1.0f,  0.0f,  2.0f,
         0.0f,  0.0f,  2.0f,
         1.0f,  0.0f,  2.0f,
         2.0f,  0.0f,  2.0f,

        -2.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         1.0f,  0.0f,  1.0f,
         2.0f,  0.0f,  1.0f,

        -2.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         0.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         2.0f,  0.0f,  0.0f,

        -2.0f,  0.0f, -1.0f,
        -1.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         1.0f,  0.0f, -1.0f,
         2.0f,  0.0f, -1.0f,

        -2.0f,  0.0f, -2.0f,
        -1.0f,  0.0f, -2.0f,
         0.0f,  0.0f, -2.0f,
         1.0f,  0.0f, -2.0f,
         2.0f,  0.0f, -2.0f,
    };

    uint32_t indicesFloor[] = {
         0,  6,  1,  0,  5,  6,
         1,  7,  2,  1,  6,  7,
         2,  8,  3,  2,  7,  8,
         3,  9,  4,  3,  8,  9,

         5, 11,  6,  5, 10, 11,
         6, 12,  7,  6, 11, 12,
         7, 13,  8,  7, 12, 13,
         8, 14,  9,  8, 13, 14,

        10, 16, 11, 10, 15, 16,
        11, 17, 12, 11, 16, 17,
        12, 18, 13, 12, 17, 18,
        13, 19, 14, 13, 18, 19,

        15, 21, 16, 15, 20, 21,
        16, 22, 17, 16, 21, 22,
        17, 23, 18, 17, 22, 23,
        18, 24, 19, 18, 23, 24
    };

    VertexArray va_floor;
    VertexBuffer vb_floor(positionsFloor, 25 * 3 * sizeof(float));

    VertexBufferLayout layoutFloor;
    layoutFloor.Push<float>(3);
    va_floor.AddBuffer(vb_floor, layoutFloor);

    IndexBuffer ib_floor(indicesFloor, 6 * 16);

    VertexArray va;
    VertexBuffer vb(positionsCube, 8 * 5 * sizeof(float));

    VertexBufferLayout layoutCube;
    layoutCube.Push<float>(3);
    layoutCube.Push<float>(2);
    va.AddBuffer(vb, layoutCube);

    IndexBuffer ib(indicesCube, 40);

    Shader shader("shaders/02vertex.glsl", "shaders/01fragment.glsl");

    Texture texture("textures/BrickWall.jpg");
    texture.Bind();

    Renderer renderer;

    double prevTime = 0.0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window))
    {
        double time = glfwGetTime();
        float dt = (float)(time - prevTime);
        prevTime = time;

        static char title[256];
        snprintf(title, 256, "dt = %.2fms, FPS = %.1f", dt * 1000.0f, 1.0f / dt);
        glfwSetWindowTitle(m_Window, title);

        /* Poll for and process events */
        glfwPollEvents();
        ProcessInput(dt);

        if (m_DebugMousePosChanged) {
            const glm::vec4& cameraPos = m_Camera.GetCameraPosition();
            printf("Current position: X: %f; Y: %f; Z: %f\n", cameraPos.x, cameraPos.y, cameraPos.z);
            m_DebugMousePosChanged = false;
        }

        /* Render here */
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", m_Camera.CalculateMVP(glm::mat4(0.5f)));
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniform4f("u_Colour", 1.0f, 0.0f, 0.0f, 1.0f);

        renderer.Clear();
        shader.Bind();
        shader.SetUniform1i("u_UseTexture", 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        renderer.Draw(va_floor, ib_floor, shader);
        shader.Bind();
        shader.SetUniform1i("u_UseTexture", 1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        renderer.Draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);
    }
}

void Sandbox::ProcessInput(float dt) {
    int dir = (int)MovementDirection::None;
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Forward;
        m_DebugMousePosChanged = true;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Backward;
        m_DebugMousePosChanged = true;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Left;
        m_DebugMousePosChanged = true;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Right;
        m_DebugMousePosChanged = true;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Up;
        m_DebugMousePosChanged = true;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_F) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Down;
        m_DebugMousePosChanged = true;
    }

    double mouse_x, mouse_y;
    glfwGetCursorPos(m_Window, &mouse_x, &mouse_y);
    glm::vec2 mouseMove(0.0f, 0.0f);
    if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        mouseMove.x = m_PrevMouseX - mouse_x;
        mouseMove.y = m_PrevMouseY - mouse_y;
    }
    m_PrevMouseX = mouse_x;
    m_PrevMouseY = mouse_y;

    m_Camera.Move((MovementDirection)dir, mouseMove, dt);
}
