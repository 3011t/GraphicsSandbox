#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec4 u_LightPos;
uniform vec4 u_ViewPos;
uniform sampler2D u_Diffuse;
uniform float u_AmbientLight;
uniform float u_Shininess;

float near = 0.1f;
float far = 10.0f;

float bumpScale = 0.05f;

void main()
{
    //colour = (u_UseTexture * texColour) + ((1 - u_UseTexture) * u_Colour);
    //colour = vec4(0.0, 0.0, 0.0, 1.0);
    //vec4 whiteAmount = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
    //colour = vec4((1 - whiteAmount.x) * texColour.x + whiteAmount.x,
    //              (1 - whiteAmount.y) * texColour.y + whiteAmount.y,
    //              (1 - whiteAmount.z) * texColour.z + whiteAmount.z,
    //              1.0);

    colour = texture(u_Diffuse, v_TexCoord);
}
