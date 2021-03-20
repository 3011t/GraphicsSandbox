#include "Sandbox.h"

void glfwErrorCallback(int error, const char* description)
{
    printf("GLFW Error %i: %s\n", error, description);
}

void GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    printf("Type[0x%x], Severity[0x%x], %s\n", type, severity, message);
}

Sandbox::Sandbox() {

}

bool Sandbox::Init() {

    glfwSetErrorCallback(glfwErrorCallback);

    /* Initialize the library */
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwTerminate();
        return false;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Make OpenGL print debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLMessageCallback, nullptr);

    return true;
}

void Sandbox::Run() {

    float positions[] = {
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray va;
    VertexBuffer vb(positions, 8 * sizeof(float));
    vb.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    ib.Bind();

    Shader shader("02vertex.glsl", "01fragment.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Colour", 0.1f, 0.2f, 0.6f, 1.0f);

    float r = 0.0f;
    float inc = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform4f("u_Colour", r, 0.2f, 0.6f, 1.0f);

        va.Bind();
        ib.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f || r < 0.0f) inc = -inc;

        r += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void Sandbox::Uninit() {
    glfwTerminate();
}
