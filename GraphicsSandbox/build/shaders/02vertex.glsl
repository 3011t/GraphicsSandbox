#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec4 v_Pos;
out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * position;
    v_Pos = position;
    v_Normal = normal;
    v_TexCoord = texCoord;
}
