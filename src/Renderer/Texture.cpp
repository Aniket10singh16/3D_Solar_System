#include "Renderer/Texture.h"
#include "glad/glad.h"
#include <iostream>


Texture::Texture()
	:textureID(0), width(0), height(0), channels(0) {
}

Texture::~Texture()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		std::cout << "[Texture] Delete texture: " << path << "\n";
	}
}

bool Texture::LoadFromFile(const std::string& filepath)
{
	path = filepath;

	// Get the file format
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filepath.c_str(), 0);

	if (format == FIF_UNKNOWN)
	{
		std::cerr << "[Texture] Failed to determine format: " << filepath << "\n";
		return false;
	}

	if (!FreeImage_FIFSupportsReading(format)) {
		std::cerr << "[texture] Format not supported: " << filepath << "\n";
		return false;
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filepath.c_str());
	if (!bitmap)
	{
		std::cerr << "[Texture] Failed to load data: " << filepath << "\n";
		return false;
	}

	// Convert to 32-bit (RGBA) for consistency
	FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

	// Unload the priginal bitmap to use the 32 bit version
	FreeImage_Unload(bitmap);

	if (!bitmap32)
	{
		std::cerr << "[Texture] Failed to convert to 32-bit: " << filepath << "\n";
		return false;
	}

	// Get image daat
	width = FreeImage_GetWidth(bitmap32);
	height = FreeImage_GetHeight(bitmap32);
	channels = 4;	// we converted to 32-bit, so it's always RGBA

	unsigned char* data = FreeImage_GetBits(bitmap32);

	// Generate OpenGL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload texture data to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);

	// Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free CPU memory
	FreeImage_Unload(bitmap32);

	std::cout << "[Texture] Loaded: " << filepath
		<< " (" << width << "x" << height << ", " << channels << " channels\n";

	return true;
}

void Texture::Bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}