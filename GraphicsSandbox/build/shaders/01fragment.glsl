#version 460 core

layout(location = 0) out vec4 colour;

in vec2 v_TexCoord;

uniform vec4 u_Colour;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColour = texture(u_Texture, v_TexCoord);
    colour = texColour; //u_Colour;
}