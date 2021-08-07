#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    //float depth = LinearizeDepth(gl_FragCoord.z) / far;
    //colour = vec4(vec3(depth), 1.0);
    //colour = vec4(v_Normal, 1.0f);
    colour = texture(u_Texture, v_TexCoord);
}
