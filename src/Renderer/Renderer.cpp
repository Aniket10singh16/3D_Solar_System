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

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

/**
* @brief Initializes global OpenGL state required for rendering.
*
* Enables depth testing. Should be called once after context creation.
* Future versions may configure additional state (blending, culling, etc).
*/
void Renderer::Initialize() {
    // GLAD is already initialized in Application constructor
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
    
    // Check OpenGL version
    std::cout << "[Renderer] OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "[Renderer] GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    
    shader = std::make_unique<Shader>("Shader/basic.vert", "Shader/basic.frag");
    
    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "[Renderer] OpenGL Error after initialization: " << err << "\n";
    }
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

void Renderer::DrawScene(const CameraRenderData& camData, int layer)
{
    (void)layer;
    
    if (!shader) {
        std::cerr << "[Renderer] ERROR: Shader is null!\n";
        return;
    }
    
    shader->Bind();

    // Upload camera-specific uniforms
    glm::mat4 view = camData.camera->GetViewMatrix();
    glm::mat4 proj = camData.camera->GetProjectionMatrix();

    shader->SetVec3("uLightDir", glm::normalize(glm::vec3(0.5f, 0.7f, 1.0f)));

    // Draw all objects in scene
    int drawCount = 0;
    static bool firstFrame = true;
    
    for (const auto* obj : sceneObjects)
    {
        if (obj->renderLayer != camData.renderLayer) continue;

        glm::mat4 model = obj->transform.GetModelMatrix();
        glm::mat3 normalMatrix = obj->transform.GetNormalMatrix();

        shader->SetMat4("uModel", model);
        shader->SetMat4("uView", view);
        shader->SetMat4("uProjection", proj);
        shader->SetMat3("uNormalMatrix", normalMatrix);

        if (firstFrame) {
            glm::vec3 pos = obj->transform.GetPosition();
            std::cout << "[Renderer] Drawing object at (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        }

        obj->mesh.Draw();
        
        // Check for OpenGL errors after draw
        GLenum err = glGetError();
        if (err != GL_NO_ERROR && firstFrame) {
            std::cerr << "[Renderer] OpenGL Error after draw: " << err << "\n";
        }
        
        drawCount++;
    }
    
    if (firstFrame) {
        std::cout << "[Renderer] Drew " << drawCount << " objects in first frame\n";
        glm::vec3 pos = camData.camera->GetPosition();
        glm::vec3 front = camData.camera->GetFront();
        std::cout << "[Renderer] Camera pos: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        std::cout << "[Renderer] Camera front: (" << front.x << ", " << front.y << ", " << front.z << ")\n";
        std::cout << "[Renderer] Camera looking at: (" << (pos.x + front.x) << ", " 
                  << (pos.y + front.y) << ", " << (pos.z + front.z) << ")\n";
        
        // Print shader ID
        std::cout << "[Renderer] Shader program ID: " << shader->GetID() << "\n";
        
        firstFrame = false;
    }

    shader->Unbind();
}

void Renderer::RenderFrame(const std::vector<CameraRenderData>& cameras)
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
        DrawScene(camData, camData.renderLayer);
    }

    // Return to default frambuffer after all cameras
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::AddRenderObject(const RenderObject& object)
{
    // Store pointer to the object instead of copying it
    // This avoids copying the Mesh which contains OpenGL resources
    sceneObjects.push_back(&object);
}

void Renderer::ResetSceneObjects()
{
    sceneObjects.clear();
}

