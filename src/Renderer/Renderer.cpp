/**
* @file Renderer.cpp
* @brief Implementation of the Renderer class for high-level rendering operations.
*
* This file provides the concrete implementation for the Renderer abstraction.
* It manages global OpenGL state, framebuffer clearing, and issues draw calls
* by combining Mesh and Shader objects. All methods assume a valid OpenGL context
* is current on the calling thread.
*
* Future-proofing notes:
* - Additional GL state setup (blending, culling) may be added in later phases.
* - Error handling and logging can be extended for robustness.
* - Draw() may be overloaded for instancing, batching, or indexed meshes.
*/
#include <Renderer/Renderer.h>
#include <glad/glad.h>
#include <iostream>

/**
* @brief Initializes global OpenGL state required for rendering.
*
* Enables depth testing. Should be called once after context creation.
* Future versions may configure additional state (blending, culling, etc).
*/
void Renderer::Initialize() {
    if (!gladLoadGLLoader) {
        std::cerr << "[Renderer] Error: GLAD not initialized before Renderer::Initialize\n";
        return;
    }
    //std::cout << "[Renderer] GLAD initialization done" << gladLoadGLLoader << std::endl;
    glEnable(GL_DEPTH_TEST);
}

/**
* @brief Clears the framebuffer with the specified color and resets depth.
*
* @param color RGBA clear color in [0,1] range.
* Clears both color and depth buffers. Future versions may support additional buffers.
*/
void Renderer::Clear(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
* @brief Draws a mesh using the provided shader.
*
* Binds the shader and issues the mesh draw call. Assumes both objects are valid
* and the OpenGL context is current. Mesh and Shader are not owned by Renderer.
*
* @param mesh   The mesh to render.
* @param shader The shader program to use.
*/
void Renderer::Draw(const Mesh& mesh, const Shader& shader) {
	shader.Use();
	mesh.Draw();
}

void Renderer::DrawScene(const Camera& camera, int layer)
{
    // Placeholder:
    // Future: Iterate over all meshes/entities and render them with MVP
    // For now: just clear with a color, camera isn't yet used

    (void)camera; // Silence unused parameter warning
}

void Renderer::RenderFrame(const std::vector<CameraRenderData> cameras)
{
    // Optimization: minimal framebuffer binds by grouping per frambuffer ID
    unsigned int currentFBO = -1;

    if (cameras.empty()) return; // Check if vector is empty

    for (const auto& camData : cameras)
    {
        if (!camData.active || !camData.camera)
            continue;

        // Bind frambuffer if needed
        if (camData.framebuffer != currentFBO)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, camData.framebuffer);
            currentFBO = camData.framebuffer;
        }

        // Set viewport for this camera
        glViewport(camData.viewport.x, camData.viewport.y,
            camData.viewport.z, camData.viewport.w);

        // Clear before each camera pass
        Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

        // Draw scene from this camera's perspective
        DrawScene(*camData.camera, camData.renderLayer);
    }

    // Return to default frambuffer after all cameras
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
