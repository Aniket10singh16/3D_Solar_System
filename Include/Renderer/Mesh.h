//Mesh header template
/**
* @file Mesh.h
* @Brief Declaration of the Mesh class for managing vertex data and OpenGL buffers.
* 
* A mesh represents a collection of vertices (and optionally indices)
* stored on the GPU. It abstructs VAO/VBO  setup and provides 
* a reusable interface for rendering geometry in the engine.
* 
* 
* A Mesh encapsulates:
*   - Vertex Buffer Object (VBO)
*   - Element Buffer Object (EBO)
*   - Vertex Array Object (VAO)
*   - Draw call parameters (vertex/index count)
* 
* Future extensions:

	Add normals, UVs, tangents, bitangents

	Add instancing support for large numbers of objects

	Integrate with Material and Shader for textured rendering
*/

#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

/**
 * @struct Vertex
 * @brief Represents a single vertex in 3D space.
 *
 * Contains position and color attributes.
 * Will later be extended to include normals, texture coordinates,
 * tangents, and bitangents for advanced rendering.
 */

struct Vertex {
	glm::vec3 position; ///< 3d position of the vertex
	glm::vec3 color;	///< EGB color of the vertex
	glm::vec3 normal;
	glm::vec2 texCoord;   
	glm::vec3 tangent;    
};

/**
 * @class Mesh
 * @brief Encapsulates an OpenGL mesh with VAO/VBO state.
 *
 * A Mesh manages its own GPU buffers (VAO, VBO, EBO if added)
 * and exposes a simple `Draw()` method. It is designed to be reusable
 * with any Shader object and does not own rendering logic itself.
 *
 * Example usage:
 * @code
 * std::vector<Vertex> vertices = {
 *     {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
 *     {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
 *     {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
 * };
 * Mesh triangle(vertices);
 * triangle.Draw();
 * @endcode
 */

class Mesh {
private:
	unsigned int VAO = 0; ///< Vertex Array Object (encapsulates buffer state)
	unsigned int VBO = 0; ///< Vertex buffer Object (encapsulates vertex data)
	unsigned int EBO = 0; ///< Element Buffer Object

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:
	/**
	 * @brief Constructs a Mesh from a given set of vertices.
	 *
	 * @param vertices A vector of Vertex structs containing position and color data.
	 */
	Mesh() = default;
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	// Move constructor and assignment (for proper OpenGL resource management)
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	// Delete copy constructor and assignment (OpenGL resources can't be copied)
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	/** @brief Uploads vertex/index data to GPU (called internally). */
	void Initialize();

	/**
	* @brief Releases GPU resources (VAO, VBO).
	*/
	~Mesh();

	/**
	 * @brief Draws the mesh to the currently bound framebuffer.
	 *
	 * Assumes that an appropriate Shader is already bound before calling.
	 * Currently uses glDrawArrays with 3 vertices (for a triangle).
	 *
	 * Future version will:
	 * - Support glDrawElements (indexed rendering)
	 * - Support variable primitive types (triangles, lines, points)
	 */

	void Draw() const;

	// Utility generators
	static Mesh CreateSphere(float radius, unsigned int sectors, unsigned int stacks);
};
