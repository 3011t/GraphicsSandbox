#include "Sandbox.h"

#include <cstdlib>

// My naming convention with these function is terrible
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

Sandbox::Sandbox()
  : m_Window(nullptr),
    m_InitStatus(false),
    m_PrevMouseX(0.0),
    m_PrevMouseY(0.0)
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        m_InitStatus = false;
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);

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

    // Automatically adjust GL viewport
    glfwSetFramebufferSizeCallback(m_Window, glfwFramebufferCallback);

    std::cout << glGetString(GL_VERSION) << std::endl;

    glfwSetKeyCallback(m_Window, glfwKeyCallback);

    // Make OpenGL print debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);
    // Enable texture blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Enable back-face culling
    glEnable(GL_CULL_FACE);
    // Enable depth test
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Enable multisapling
    glEnable(GL_MULTISAMPLE);


    Camera viewerCam;
    viewerCam.SetProjection(glm::radians(90.0f), (16.0f / 9.0f), 0.1f, 1000.0f);
    viewerCam.SetView(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    viewerCam.SetMovementSpeed(3.0f);
    viewerCam.SetSensitivity(1.0f);

    m_Scene.AddCamera(viewerCam);
    m_Scene.AddShader("basic", "shaders/01_vs_basic.glsl", "shaders/01_fs_basic.glsl");
    m_Scene.SetShader("basic");
    // Add sponza model
    m_Scene.AddModelFromFile("Sponza", "assets/sponza_scene/crytek-sponza.obj");
    m_Scene.AddInstance({ "Sponza", glm::scale(glm::mat4(1.0f), glm::vec3(0.01f)) });


    glfwGetCursorPos(m_Window, &m_PrevMouseX, &m_PrevMouseY);

    m_InitStatus = true;
}

Sandbox::~Sandbox() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Sandbox::Run() {
    Renderer renderer;
    renderer.SetClearColour({ 0.1f, 0.4f, 0.7f, 1.0f });

    glm::vec3 lightSourcePos = {0.0f, 6.f, 0.0f};

    double prevTime = 0.0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window)) {
        double time = glfwGetTime();
        float dt = (float)(time - prevTime);
        prevTime = time;

        static char title[256];
        snprintf(title, 256, "dt = %.2fms, FPS = %.1f", dt * 1000.0, 1.0f / dt);
        glfwSetWindowTitle(m_Window, title);

        /* Poll for and process events */
        glfwPollEvents();
        InputEvents events = ProcessInput(dt);

        m_Scene.Update(events);

        /* Render here */
        renderer.Clear();
        renderer.Draw(m_Scene);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);
    }
}

InputEvents Sandbox::ProcessInput(float dt) {
    int dir = (int)MovementDirection::None;
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Forward;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Backward;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Left;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Right;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Up;
    }
    if (glfwGetKey(m_Window, GLFW_KEY_F) == GLFW_PRESS) {
        dir |= (int)MovementDirection::Down;
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

    return {dt, (MovementDirection)dir, mouseMove};
}
