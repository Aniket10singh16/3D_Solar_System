// Shader header template
/**
 * @file Shader.h
 * @brief A basic shader class implementation that manages GLSL program.
 */


#pragma once
#include <glm/glm.hpp>
#include <string>

 /**
  * @class Shader
  * @brief Handles GLSL programs creation and deletion.
  *
  * Shader is responsible for creating shader program, attaching shader code to shader compiler, compile the shader,
  * delete the shader program.
  */

class Shader {
public:
	unsigned int ID;

	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Use() const;
};