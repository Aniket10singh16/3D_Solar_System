#version 460 core
in vec3 FragPos;
in vec3 FragNormal;
in vec3 FragColor;
in vec2 TexCoord;
in vec3 Tangent;

// Output
out vec4 FragOutput;

//  Material structure
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    vec3 emissive;

    sampler2D diffuseMap;
    sampler2D specularMap;

    int useDiffuseMap;
    int useSpecularMap;
    int useNormalMap;
};

uniform Material material;

// Light uniforms
uniform vec3 uLightDir;
uniform vec3 uLightColor;
uniform vec3 uViewPos;      // Camera position

void main()
{
    // get base color (from texture or material color)
    vec3 baseColor;
    if (material.useDiffuseMap == 1) {
        baseColor = texture(material.diffuseMap, TexCoord).rgb;
    }
    else {
        baseColor = material.diffuse;
    }

    // Normalize vectors
    vec3 norm = normalize(FragNormal);
    vec3 lightDir = normalize(uLightDir);
    vec3 viewDir = normalize(uViewPos - FragPos);

    // Ambient lighting
    vec3 ambient = material.ambient * baseColor;

    // Diffuse lighting 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor * baseColor;

    // Specular lighting (Phong)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Get specular intensity from map if available
    vec3 specularColor = material.specular;
    if (material.useSpecularMap == 1) {
        specularColor = texture(material.specularMap, TexCoord).rgb;
    }
    
    vec3 specular = spec * uLightColor * specularColor;

    // Combine lighting 
    vec3 result = ambient + diffuse + specular + material.emissive;

    FragOutput = vec4(result, 1.0);
}

