#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec4 u_LightPos;
uniform vec4 u_ViewPos;
uniform sampler2D u_Diffuse;
uniform sampler2D u_Specular;
uniform sampler2D u_Normal;
uniform sampler2D u_Bump;
uniform sampler2D u_Occlusion;
uniform float u_AmbientLight;
uniform float u_Shininess;

float near = 0.1f;
float far = 10.0f;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return ((2.0 * near * far) / (far + near - z * (far - near))) / far;
}

void main()
{
    //colour = (u_UseTexture * texColour) + ((1 - u_UseTexture) * u_Colour);
    //colour = vec4(0.0, 0.0, 0.0, 1.0);
    //vec4 whiteAmount = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
    //colour = vec4((1 - whiteAmount.x) * texColour.x + whiteAmount.x,
    //              (1 - whiteAmount.y) * texColour.y + whiteAmount.y,
    //              (1 - whiteAmount.z) * texColour.z + whiteAmount.z,
    //              1.0);
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

    vec3 albedo = texture(u_Diffuse, v_TexCoord).rgb;
    vec3 noSample = texture(u_Normal, v_TexCoord.st).rgb;
    float specSample = texture(u_Specular, v_TexCoord.st).r;
    float occlusion = texture(u_Occlusion, v_TexCoord.st).r;

    vec3 lightDir = normalize(u_LightPos - v_Pos).xyz;
    float lengthSq = dot(lightDir, lightDir);
    float length = sqrt(lengthSq);
    lightDir /= length;

    vec3 viewDir = normalize(u_ViewPos.xyz - v_Pos.xyz).xyz;
    vec3 halfDir = reflect(-lightDir, v_Normal).xyz;

    float horizon = clamp(1.0f + dot(v_Normal, lightDir), 0.0f, 1.0f);
    horizon *= horizon;
    horizon *= horizon;
    horizon *= horizon;
    horizon *= horizon;

    vec3 ambient = vec3(0.1f, 0.1f, 0.1f) * occlusion;
    vec3 diffuse = horizon * max(0.0f, dot(v_Normal, lightDir)) * lightColour / lengthSq;
    vec3 specular = horizon * specSample * lightColour * pow(max(0.0f, dot(v_Normal, halfDir)), 64.0f) / lengthSq;

    colour = vec4(albedo * (ambient + diffuse) + specular, 1.0);
}
