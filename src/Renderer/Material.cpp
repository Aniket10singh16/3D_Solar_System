#include "Renderer/Material.h"
#include <iostream>

Material::Material() { }

void Material::SetProperties(const MaterialProperties& props)
{
	properties = props;
}

void Material::SetAmbientColor(const glm::vec3& color) {
    properties.ambient = color;
}

void Material::SetDiffuseColor(const glm::vec3& color) {
    properties.diffuse = color;
}

void Material::SetSpecularColor(const glm::vec3& color) {
    properties.specular = color;
}

void Material::SetShininess(float shine) {
    properties.shininess = shine;
}

void Material::SetEmissiveColor(const glm::vec3& color) {
    properties.emissive = color;
}

void Material::SetTexture(Render::TextureType type, Texture* texture)
{
    if (texture)
    {
        textures[type] = texture;
    }
    else
    {
        textures.erase(type);
    }
}

bool Material::HasTexture(Render::TextureType type) const {
    return textures.find(type) != textures.end();
}

void Material::Apply(Shader& shader) const
{
    // Set material properties as uniforms
    shader.SetVec3("material.ambient", properties.ambient);
    shader.SetVec3("material.diffuse", properties.diffuse);
    shader.SetVec3("material.specular", properties.specular);
    shader.SetFloat("material.shininess", properties.shininess);
    shader.SetVec3("material.emissive", properties.emissive);

    // Helper lambda to bind texture if it exists
    auto BindTextureIfPresent = [&](Render::TextureType type, const std::string& uniformName,
        const std::string& useFlagName, int unit) {
            if (textures.count(type))
            {
                textures.at(type)->Bind(unit);
                shader.SetInt(uniformName, unit);
                shader.SetInt(useFlagName, 1);
            }
            else
            {
                shader.SetInt(useFlagName, 0);
            }
        };

    // Bind supported textures
    // Unit 0: Diffuse
        BindTextureIfPresent(Render::TextureType::Diffuse, "material.diffuseMap", "material.useDiffuseMap", 0);

        // Unit 1: Specular
        BindTextureIfPresent(Render::TextureType::Specular, "material.specularMap", "material.useSpecularMap", 1);

        // Unit 2: Normal
        BindTextureIfPresent(Render::TextureType::Normal, "material.normalMap", "material.useNormalMap", 2);
};