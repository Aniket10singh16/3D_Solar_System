/**
 * @file CameraManager.h
 * @brief Declares the CameraManager class and supporting structs for multi-camera management.
 *
 * This version supports multiple active cameras at once.
 * Each camera can render to:
 *  - A specific framebuffer (default or offscreen)
 *  - A defined viewport (for split-screen, minimap, etc.)
 *  - A specific render layer (to limit which objects are visible)
 *
 * The Renderer will query all active cameras each frame
 * and perform one render pass per camera.
 */

#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <glm/glm.hpp>
#include <Scene/Camera.h>

/**
* @struct CameraRenderData
* @brief Describes how a camera should render in a given frame.
*/

struct CameraRenderData
{
    std::string name;      ///< Identifier (e.g., "main", "minimap")
    Camera* camera = nullptr; ///< Pointer to the camera
    bool active = true;    ///< Whether to render this camera this frame
    glm::ivec4 viewport;   ///< (x, y, width, height)
    unsigned int framebuffer = 0; ///< 0 = default framebuffer (screen)
    int renderLayer = 0;   ///< Optional: restrict rendering to specific layer(s)
};

/**
 * @class CameraManager
 * @brief Manages all cameras in the application.
 *
 * Responsibilities:
 *  - Add/remove cameras
 *  - Mark cameras active/inactive
 *  - Provide all active cameras to the Renderer
 */

class CameraManager
{
private:
    std::unordered_map<std::string, CameraRenderData> cameras;

public:
    /**
    * @brief Adds or updates a camera in the manager.
    * @param name Unique identifier.
    * @param camera Pointer to a Camera instance (owned externally).
    * @param viewport Viewport rectangle (x, y, width, height).
    * @param framebuffer OpenGL framebuffer ID (0 = default).
    * @param layer Render layer mask (default = 0).
    */
    void AddCamera(const std::string& name,
        Camera* camera,
        const glm::ivec4& viewport,
        unsigned int framebuffer = 0,
        int layer = 0);

    /**
 * @brief Sets whether a camera is active for rendering.
 */
    void SetActive(const std::string& name, bool active);

    /**
     * @brief Retrieves render data for a named camera.
     */
    CameraRenderData& GetCameraData(const std::string& name);

    /**
     * @brief Returns all currently active cameras for this frame.
     */
    std::vector<CameraRenderData> GetActiveCameras() const;

    /**
    * @brief Returns first active camera for this frame.
    */
    Camera& GetActive() const;
};