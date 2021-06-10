#version 460 core

layout(location = 0) out vec4 colour;

in vec2 v_TexCoord;

uniform int u_UseTexture;
uniform vec4 u_Colour;
uniform sampler2D u_Texture;

float near = 0.1f;
float far = 10.0f;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return ((2.0 * near * far) / (far + near - z * (far - near))) / far;
}

void main()
{
    vec4 texColour = texture(u_Texture, v_TexCoord);
    //colour = (u_UseTexture * texColour) + ((1 - u_UseTexture) * u_Colour);
    //colour = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 whiteAmount = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
    colour = vec4((1 - whiteAmount.x) * texColour.x + whiteAmount.x,
                  (1 - whiteAmount.y) * texColour.y + whiteAmount.y,
                  (1 - whiteAmount.z) * texColour.z + whiteAmount.z,
                  1.0);
}
