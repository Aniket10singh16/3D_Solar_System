#pragma once
#include <string>
#include <FreeImage.h>
/**
@file Texture.h
@brief This is wrapper stb_image.h header to load an image as use as a textre.

This class is responsible:
	- Load a texture image
	- bind the image to texture unit for rendering
*/



class Texture 
{
private:
	unsigned int textureID;	// opengl texture handle
	int width, height;	// Image dimensions
	int channels;		// Number of color channels (3=RGB, 4=RGB)
	std::string path;	// File path (for debugging)

public:
	Texture();
	~Texture();

	// Delete copy constructor/assigment (texture shouldn't be copied)
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	// Load texture from file
	bool LoadFromFile(const std::string& filePath);

	// Bind texture to a texture unit for rendering
	void Bind(unsigned int unit = 0) const;
	void Unbind() const;

	// Getters
	unsigned int GetID() const { return textureID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	std::string GetPath() const { return path; }
};
