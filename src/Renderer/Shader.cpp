/**
 * @file Shader.cpp
 * @brief Implementation of the Shader class for managing GLSL shader programs.
 */
#include <Renderer/Shader.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>


// -----------------------------------------------------
// Constructor / Destructor
// -----------------------------------------------------

/**
 * @brief Constructs a Shader object by compiling and linking vertex and fragment shaders.
 * @param vertexSrc The source code for the vertex shader.
 * @param fragmentSrc The source code for the fragment shader.
 */
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexCode = LoadFile(vertexPath);
	std::string fragmentCode = LoadFile(fragmentPath);

	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	programID= glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	int success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char inforLog[1024];
		glGetProgramInfoLog(programID, 1024, nullptr, inforLog);
		throw std::runtime_error("Shader link error:\n" + std::string(inforLog));
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/**
 * @brief Destructor. Deletes the shader program.
 */
Shader::~Shader() 
{
	if(programID)
		glDeleteProgram(programID);
}


// -----------------------------------------------------
// Helper Functions
// -----------------------------------------------------

std::string Shader::LoadFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error("Failed to open shader file: " + path);

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

 /**
  * @brief Compiles a shader of the given type from source code.
  * @param type The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
  * @param source The GLSL source code for the shader.
  * @return The compiled shader ID.
  */
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		std::string typeName = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
		throw std::runtime_error(typeName + " shader compile error:\n" + std::string(infoLog));
	}
	return shader;
}

int Shader::GetUniformLocation(const std::string& name) const
{
	// Cached lookup to avoid glGetUniformLocation call every frame
	if (uniformCache.find(name) != uniformCache.end())
		return uniformCache[name];

	int location = glGetUniformLocation(programID, name.c_str());
	if (location == -1)
		std::cerr << "[Shader] Warning: uniform '" << name << "' not found or unused.\n";

	uniformCache[name] = location;
	return location;
}

// -----------------------------------------------------
// Shader Usage
// -----------------------------------------------------

void Shader::Bind() const { glUseProgram(programID); }
void Shader::Unbind() const { glUseProgram(0); }

// -----------------------------------------------------
// Uniform Setters
// -----------------------------------------------------

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}