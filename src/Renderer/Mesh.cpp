#include <Renderer/Mesh.h>
#include <glad/glad.h>


/**
 * @brief Initializes the Mesh by uploading vertex data to GPU buffers.
 *
 * Creates and binds a VAO + VBO, then sets up vertex attribute pointers
 * for position and color. At this stage, each vertex contains 6 floats:
 *  - vec3 position (x, y, z)
 *  - vec3 color (r, g, b)
 *
 * @param vertices The list of vertices to upload.
 */

Mesh::Mesh(const std::vector<Vertex>& vertices) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		vertices.data(), GL_STATIC_DRAW);

	// Vertex attribute 0 -> position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex attribute 1 -> color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // unbind VAO
}

/**
* @brief Deletes VAO and VBO from GPU memory.
*/
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

/**
 * @brief Renders the Mesh.
 *
 * Issues a glDrawArrays call to render the vertex buffer.
 * Currently assumes the mesh has 3 vertices (for a test triangle).
 *
 * @note This will be extended to use a stored vertex count or index buffer.
 */

void Mesh::Draw() const{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3); // TODO: make vertex count configurable
	glBindVertexArray(0);
}