#version 460 core

layout(location = 0) out vec4 colour;

struct Light {
    float range;
    float radius;
    float power;
    bool isDirectional;
    vec3 position;
    vec3 direction;
    vec3 colour;
};

// Vertex data
in vec4 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;
// Camera position and direction
in vec3 v_ViewPos;
in vec3 v_ViewDir;
// Material uniforms
uniform vec3 u_Ambient;
uniform vec3 u_Diffuse;
uniform vec3 u_Specular;
uniform float u_Shininess;
uniform sampler2D u_DiffuseTexture;
uniform bool u_HasTexture;

// Blinn-Phong shading was taken from lecture slides for NPGR019

float blinnPhongSpecular(
    vec3 normal,
    vec3 viewDir,
    vec3 lightDir,
    float shininess)
{
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    return pow(specAngle, shininess * 4.0);
}

float phongSpecular(
    vec3 normal,
    vec3 viewDir,
    vec3 lightDir,
    float shininess)
{
    vec3 reflectDir = reflect(-lightDir, normal);
    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    return pow(specAngle, shininess);
}

vec3 blinnPhong(
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
        specular = blinnPhongSpecular(normal, viewDir, lightDir, shininess);
    }
    return ambientColor + (diffuseColor * lambertian * lightColor + specColor * specular * lightColor) * lightPower;
}

// Lights, provided via uniform buffer
layout (std140) uniform u_LightsBlock {
    Light lights[8];
};

void main()
{
    vec4 texColour = texture(u_DiffuseTexture, v_TexCoord);

    // If a pixel is transparent, ignore it
    if(texColour.a < 0.5) discard;

    // Ambient colour
    colour = texColour * 0.1f;
    colour.w = 1.0;

    for (int i = 0; i < 2; ++i) {
        // Figure out the different lightsources contribution

        // If the lightsource is directional, ignore radius and range?

        if (lights[i].isDirectional) {
            colour += vec4(blinnPhong(vec3(0.0), texColour.rgb,
                u_Specular, v_Normal, v_ViewDir, lights[i].colour,
                normalize(lights[i].direction), lights[i].power, u_Shininess), texColour.a);
        }
        else if (distance(lights[i].position, v_Pos.xyz) <= lights[i].range) {
            colour += vec4(blinnPhong(vec3(0.0), texColour.rgb,
                u_Specular, v_Normal, v_ViewDir, lights[i].colour,
                normalize(lights[i].direction), lights[i].power, u_Shininess), texColour.a);
        }
    }
}
