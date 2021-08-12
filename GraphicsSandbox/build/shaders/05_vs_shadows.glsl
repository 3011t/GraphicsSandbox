#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec4 v_Pos;
out vec3 v_Normal;
out vec2 v_TexCoord;

out vec3 v_ViewPos;
out vec3 v_ViewDir;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    v_ViewPos = vec3(u_View[3][0], u_View[3][1], u_View[3][2]);
    v_ViewDir = vec3(u_View[2][0], u_View[2][1], u_View[2][2]);

    gl_Position = u_Projection * u_View * u_Model * position;
    v_Pos = u_Model * position;
    v_Normal = normal;
    v_TexCoord = texCoord;
}
