#include <Renderer/Mesh.h>
#include <glad/glad.h>
#include <iostream>


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

Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds) 
	: vertices(verts), indices(inds)
{
	Initialize();
}

// Move constructor
Mesh::Mesh(Mesh&& other) noexcept
	: VAO(other.VAO), VBO(other.VBO), EBO(other.EBO),
	  vertices(std::move(other.vertices)), indices(std::move(other.indices))
{
	// Invalidate the other mesh's handles so its destructor doesn't delete them
	other.VAO = 0;
	other.VBO = 0;
	other.EBO = 0;
}

// Move assignment
Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other) {
		// Clean up existing resources
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		// Transfer ownership
		VAO = other.VAO;
		VBO = other.VBO;
		EBO = other.EBO;
		vertices = std::move(other.vertices);
		indices = std::move(other.indices);

		// Invalidate other
		other.VAO = 0;
		other.VBO = 0;
		other.EBO = 0;
	}
	return *this;
}


void Mesh::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), 
		vertices.data(), GL_STATIC_DRAW);

	// Upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
		indices.data(), GL_STATIC_DRAW);

	// Vertex layout:
	// 0 -> position(vec3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// 1 -> normal (vec3)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//2 -> color (vec3)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

/**
* @brief Deletes VAO and VBO from GPU memory.
*/
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
	if (VAO == 0 || indices.empty()) {
		std::cerr << "[Mesh] Error: Cannot draw - VAO=" << VAO << ", indices=" << indices.size() << "\n";
		return;
	}
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


/**
 * @brief Procedurally generates a UV sphere.
 *
 * @param radius Sphere radius
 * @param sectors Longitude divisions (horizontal)
 * @param stacks  Latitude divisions (vertical)
 *
 * Vertex formula:
 *   x = r * cos(u) * sin(v)
 *   y = r * sin(u) * sin(v)
 *   z = r * cos(v)
 *
 * where u ∈ [0, 2π], v ∈ [0, π]
 */
Mesh Mesh::CreateSphere(float radius, unsigned int sectors, unsigned int stacks)
{
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;

	const float PI = 3.14159265359f;
	float sectorsStep = 2 * PI / sectors;
	float stackStep = PI / stacks;

	for (unsigned int i = 0; i <= stacks; ++i)
	{
		float stackAngle = PI / 2 - i * stackStep; // from + pi/2 to -pi/2
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for (unsigned int j = 0; j <= sectors; ++j)
		{
			float sectorAngle = j * sectorsStep;

			Vertex v;
			v.position.x = xy * cosf(sectorAngle);
			v.position.y = xy * sinf(sectorAngle);
			v.position.z = z;

			// Normal for a sphere is the normalized position vector (pointing outward from center)
			v.normal = glm::normalize(v.position / radius);
			v.color = glm::vec3((float)j / sectors, (float)i / stacks, 1.0f);
			verts.push_back(v);
		}
	}

	// build indices 
	for (unsigned int i = 0; i < stacks; ++i)
	{
		unsigned int k1 = i * (sectors + 1);
		unsigned int k2 = k1 + sectors + 1;
		
		for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				inds.push_back(k1);
				inds.push_back(k2);
				inds.push_back(k1 + 1);
			}
			if (i != (stacks - 1))
			{
				inds.push_back(k1 + 1);
				inds.push_back(k2);
				inds.push_back(k2 + 1);
			}
		}
	}

	std::cout << "[Mesh] Created sphere: " << verts.size() << " vertices, " << inds.size() << " indices\n";
	return Mesh(verts, inds);
}