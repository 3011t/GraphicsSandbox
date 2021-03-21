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

    m_Camera.SetProjection(glm::radians(90.0f), (16.0f / 9.0f), 0.01f, 100.0f);
    m_Camera.SetView(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Camera.SetMovementSpeed(1.0f);
    m_Camera.SetSensitivity(0.01f);

    glfwGetCursorPos(m_Window, &m_PrevMouseX, &m_PrevMouseY);

    m_InitStatus = true;
}

Sandbox::~Sandbox() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Sandbox::Run() {

    float positions[] = {
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    };

    uint32_t indices[] = {
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

    VertexArray va;
    VertexBuffer vb(positions, 8 * 5 * sizeof(float));
    vb.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 40); // <- should be 40, disabled for ease of use for now
    ib.Bind();

    Shader shader("shaders/02vertex.glsl", "shaders/01fragment.glsl");
    shader.Bind();

    Texture texture("textures/BrickWall.jpg");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

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

        /* Render here */
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", m_Camera.CalculateMVP(glm::mat4(0.5f)));

        renderer.Clear();
        renderer.Draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);
    }
}

void Sandbox::ProcessInput(float dt) {
    int dir = (int)MovementDirection::None;
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        dir |= (int)MovementDirection::Forward;

    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        dir |= (int)MovementDirection::Backward;

    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        dir |= (int)MovementDirection::Left;

    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        dir |= (int)MovementDirection::Right;

    if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS)
        dir |= (int)MovementDirection::Up;

    if (glfwGetKey(m_Window, GLFW_KEY_F) == GLFW_PRESS)
        dir |= (int)MovementDirection::Down;

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
