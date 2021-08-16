#version 460 core

layout(location = 0) out vec4 colour;

in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec3 u_ViewDir;

uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec3 u_Specular;
uniform float u_Shininess;
uniform sampler2D u_DiffuseTexture;

// Blinn-Phong shading was taken from lecture slides for NPGR019

float blinn_phong_specular(
    vec3 normal,
    vec3 viewDir,
    vec3 lightDir,
    float shininess)
{
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    return pow(specAngle, shininess * 4.0);
}

float phong_specular(
    vec3 normal,
    vec3 viewDir,
    vec3 lightDir,
    float shininess)
{
    vec3 reflectDir = reflect(-lightDir, normal);
    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    return pow(specAngle, shininess);
}

vec3 blinn_phong(
    vec3 ambientColor,
    vec3 diffuseColor,
    vec3 specColor,
    vec3 normal,
    vec3 viewDir,
    vec3 lightColor,
    vec3 lightDir,
    float lightPower,
    float shininess)
{
    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;
    if (lambertian > 0.0) {
        specular = blinn_phong_specular(normal, viewDir, lightDir, shininess);
    }
    return ambientColor + (diffuseColor * lambertian * lightColor + specColor * specular * lightColor) * lightPower;
}


void main()
{
    vec4 texColour = texture(u_DiffuseTexture, v_TexCoord);

    if(texColour.a < 0.5) discard;

    colour = vec4(blinn_phong(texColour.rgb * 0.1f,
                              texColour.rgb,
                              u_Specular,
                              v_Normal,
                              u_ViewDir,
                              vec3(1.0f, 1.0f, 1.0f),
                              normalize(vec3(2, 8, 2)),
                              1.0,
                              u_Shininess), texColour.a);

}
