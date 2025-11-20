#pragma once
#include <Renderer/Texture.h>
#include <Renderer/Shader.h>
#include <Renderer/TextureEnums.h>
#include <memory>
#include <map>

//	Material properties structure
struct MaterialProperties {
	glm::vec3 ambient;	// Color in shadow (base color)
	glm::vec3 diffuse;	// Main surface color
	glm::vec3 specular; // Highlight color
	float shininess;
	glm::vec3 emissive;	// Self-illumination (for sun, glowing objects)

	// Default constructor with reasonable values

	MaterialProperties()
		: ambient(0.2f, 0.2f, 0.2f)
		, diffuse(0.8f, 0.8f, 0.8f)
		, specular(0.5f, 0.5f, 0.5)
		, shininess(32.0f)
		, emissive(0.0f, 0.0f, 0.0f)
	{}
};

class Material {
private:
	MaterialProperties properties;

	// Dynamic storage for textures
	std::map<Render::TextureType, Texture*> textures;

public:
	Material();
	~Material() = default;

	// Property setters
	void SetProperties(const MaterialProperties& props);
	void SetAmbientColor(const glm::vec3& color);
	void SetDiffuseColor(const glm::vec3& color);
	void SetSpecularColor(const glm::vec3& color);
	void SetShininess(float shine);
	void SetEmissiveColor(const glm::vec3& color);

	// Teture setters
	void SetTexture(Render::TextureType type, Texture* texture);

	// Apply material to shader (binds textures and sets uniforms)
	void Apply(Shader& shader) const;

	// Getters
	MaterialProperties& getProperties() { return properties; }
	const MaterialProperties& GetProperties() const { return properties; }

	// Check if specific texture type exists
	bool HasTexture(Render::TextureType type) const;
};