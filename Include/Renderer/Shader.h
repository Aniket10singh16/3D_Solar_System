// Shader header template
/**
 * @file Shader.h
 * @brief A basic shader class implementation that manages GLSL program.
 */


#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

 /**
  * @class Shader
  * @brief Handles GLSL programs creation and deletion.
  *
  * Shader is responsible for creating shader program, attaching shader code to shader compiler, compile the shader,
  * delete the shader program.
  */

class Shader {
private:
	unsigned int programID = 0;
	mutable std::unordered_map<std::string, int> uniformCache;

	// Internal helpers
	unsigned int CompileShader(unsigned int type, const std::string& source);
	std::string LoadFile(const std::string& path);
	int GetUniformLocation(const std::string& name) const;

public:
	Shader() = default;
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int GetID() const { return programID; }

	// Uniform Setters
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetMat3(const std::string& name, const glm::mat3& value) const;
	void SetMat4(const std::string& name, const glm::mat4& value) const;
};