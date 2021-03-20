#include "Sandbox.h"

void glfwErrorCallback(int error, const char* description)
{
    printf("GLFW Error %i: %s\n", error, description);
}

void GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    printf("Type[0x%x], Severity[0x%x], %s\n", type, severity, message);
}

Sandbox::Sandbox() {
    glfwSetErrorCallback(glfwErrorCallback);

    /* Initialize the library */
    if (!glfwInit())
        m_InitStatus = false;

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        m_InitStatus = false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL()) {
        glfwTerminate();
        m_InitStatus = false;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Make OpenGL print debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_InitStatus = true;
}

Sandbox::~Sandbox() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Sandbox::Run() {

    float positions[] = {
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    vb.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    ib.Bind();

    Shader shader("shaders/02vertex.glsl", "shaders/01fragment.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Colour", 0.1f, 0.2f, 0.6f, 1.0f);

    Texture texture("textures/BrickWall.jpg");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    float r = 0.0f;
    float inc = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window))
    {
        /* Render here */
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Colour", r, 0.2f, 0.6f, 1.0f);

        renderer.Draw(va, ib, shader);

        if (r > 1.0f || r < 0.0f) inc = -inc;

        r += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
