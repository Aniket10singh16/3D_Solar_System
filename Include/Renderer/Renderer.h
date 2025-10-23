//Renderer header template
/**
* @file Renderer.h
* @brief Abstraction of rendering layer
*
* The renderer owns the shader and mesh classes and ties them together to render the object.
*
* Future extensions:
* 
*/
#pragma once
#include <Renderer/Shader.h>
#include <Renderer/Mesh.h>
#include <glm/glm.hpp>
#include <Scene/CameraManager.h>
#include <Scene/Camera.h>

 /**
  * @class Renderer
  * @brief High-level rendering façade that issues draw calls using Mesh and Shader objects.
  *
  * The Renderer provides a small, stable surface for the rest of the engine to perform rendering.
  * It does NOT own Mesh or Shader instances — callers retain ownership and must ensure their lifetime
  * spans any calls into Renderer that reference them.
  *
  * Responsibilities:
  * - Hold and configure global GL state required for basic rendering (viewport, depth, blending, etc).
  * - Provide simple entry points for clearing and drawing.
  * - Validate preconditions (GL context, initialization) and log or return errors where appropriate.
  *
  * Initialization and context requirements:
  * - Initialize() must be called once after a valid OpenGL context is created and made current.
  * - The GL context must remain current on the thread invoking rendering methods.
  *
  * Threading and safety:
  * - Renderer is not thread-safe. All calls must be made from the thread that owns the GL context unless
  *   an explicit command-queue / context-sharing mechanism is added in a later phase.
  *
  * Error handling policy:
  * - Methods should prefer to log GL errors rather than throw exceptions in the rendering path for
  *   predictable real-time behaviour. Future phases may add configurable policies (exceptions, assert,
  *   or callback).
  *
  * Future-proofing notes (planned phases):
  * - Phase 2: Add RenderQueue, state sorting, and simple materials (uniform/texture binding helpers).
  * - Phase 3: Support instanced rendering, indexed meshes, and multiple viewports.
  * - Phase 4: Add profiling hooks, debug overlays, and render passes for deferred shading.
  *
  * Example usage:
  * @code
  * Renderer renderer;
  * renderer.Initialize(); // after creating GL context
  * renderer.Clear({0.1f, 0.1f, 0.1f, 1.0f});
  * shader.Use();
  * renderer.Draw(mesh, shader);
  * @endcode
  */
class Renderer {
public:
	/**
	 * @brief Prepare renderer global state and subsystems.
	 *
	 * Must be called once after an OpenGL context has been created and made current.
	 * Typical work: setup default GL state (viewport, depth test, face culling), load debug callbacks.
	 *
	 * Idempotency: calling Initialize() multiple times should be safe but is implementation-defined.
	 */
	void Initialize();

	/**
	 * @brief Clear the default framebuffer with the specified color.
	 *
	 * This will typically clear color and depth buffer. The exact buffers cleared are an implementation
	 * detail and may change if additional framebuffers / targets are supported in future phases.
	 *
	 * @param color RGBA clear color in the [0,1] range.
	 */
	void Clear(const glm::vec4& color);

	/**
	 * @brief Issue draw commands for a single mesh using the provided shader.
	 *
	 * Preconditions:
	 * - A valid OpenGL context must be current.
	 * - shader.Use() should be called before Draw if the shader needs to be bound explicitly.
	 * - The Mesh and Shader objects must remain valid for the duration of the call.
	 *
	 * Ownership:
	 * - Renderer does not take ownership of mesh or shader.
	 *
	 * Future enhancements:
	 * - Overloads accepting transform matrices, per-draw uniform parameters, and instancing counts.
	 * - A DrawBatch(...) API that accepts multiple meshes/shaders to allow internal state sorting.
	 *
	 * @param mesh  The Mesh to draw (read-only).
	 * @param shader The Shader to use for drawing (read-only).
	 */
	void Draw(const Mesh& mesh, const Shader& shader);

	/**
	 * @brief Renders the scene from all active cameras.
	 * @param cameras List of active cameras from CameraManager.
	 *
	 * Each camera may:
	 *  - Use a different framebuffer
	 *  - Define its own viewport (for split-screen, minimap, etc.)
	 *  - Render different object layers (future optimization)
	 */
	void RenderFrame(const std::vector<CameraRenderData> cameras);

	/**
	 * @brief Draws the scene from the perspective of a given camera.
	 * @param camera The active camera to render with.
	 *
	 * In Phase 2, this will render spheres (planets).
	 */
	void DrawScene(const Camera& camera, int layer);
};