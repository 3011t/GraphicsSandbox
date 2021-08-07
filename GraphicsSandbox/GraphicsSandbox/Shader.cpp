#include "Shader.h"

Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
  : m_VertexFilePath(vertex_filepath),
    m_FragmentFilePath(fragment_filepath)
{
    m_RendererID = CreateShader(GetShaderSource(m_VertexFilePath), GetShaderSource(m_FragmentFilePath));
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::Reload() {
    glDeleteProgram(m_RendererID);
    m_RendererID = CreateShader(GetShaderSource(m_VertexFilePath), GetShaderSource(m_FragmentFilePath));
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3) {
    glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int32_t value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int32_t Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    m_UniformLocationCache[name] = location;

    if(location == -1) printf("Warning: uniform '%s' doesn't exist!\n", name.c_str());

	return location;
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf(message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

std::string Shader::GetShaderSource(const std::string& filename) {
    std::ifstream file(filename);

    std::string shaderSource = "";
    std::string line;
    while (getline(file, line)) {
        shaderSource += line + "\n";
    }
    file.close();
    return shaderSource;
}

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    uint32_t program = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}