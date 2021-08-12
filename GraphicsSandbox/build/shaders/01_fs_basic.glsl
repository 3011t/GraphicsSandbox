#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_DiffuseTexture;

void main()
{
    vec4 texColour = texture(u_DiffuseTexture, v_TexCoord);

    if(texColour.a < 0.5) discard;

    colour = texColour;
}
