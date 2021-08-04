#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    //colour = texture(u_Texture, v_TexCoord);

    vec4 normalCol = vec4(v_Normal.x, v_Normal.y, v_Normal.z, 1.0f);
    normalCol += 1;
    normalCol /= 2;
    colour = normalCol;
}
