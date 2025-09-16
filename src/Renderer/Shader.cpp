/**
 * @file Shader.cpp
 * @brief Implementation of the Shader class for managing GLSL shader programs.
 */
#include <Renderer/Shader.h>
#include <glad/glad.h>
#include<iostream>

 /**
  * @brief Compiles a shader of the given type from source code.
  * @param type The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
  * @param source The GLSL source code for the shader.
  * @return The compiled shader ID.
  */
static unsigned int CompileShader(GLenum type, const std::string& source) {
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::cerr << "Shader compile error" << log << std::endl;
	}
	return shader;
}

/**
 * @brief Constructs a Shader object by compiling and linking vertex and fragment shaders.
 * @param vertexSrc The source code for the vertex shader.
 * @param fragmentSrc The source code for the fragment shader.
 */
Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/**
 * @brief Destructor. Deletes the shader program.
 */
Shader::~Shader() {
	glDeleteProgram(ID);
}

/**
 * @brief Activates the shader program for rendering.
 */
void Shader::Use() const {
	glUseProgram(ID);
}