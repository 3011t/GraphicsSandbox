#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

float near = 1.0f;
float far = 100.0f;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    colour = vec4(vec3(depth), 1.0);
}
