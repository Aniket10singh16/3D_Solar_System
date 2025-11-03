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
#include <algorithm>
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
    std::vector<CameraRenderData> activeCameras;
    Camera* mainCamera = nullptr;

public:
    CameraManager() = default;
    ~CameraManager();

    // Prevent copying to avoid double-delete issues
    CameraManager(const CameraManager&) = delete;
    CameraManager& operator=(const CameraManager&) = delete;

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
     * @brief Creates the main camera using the current screen resolution.
     * @param windowWidth  Screen width in pixels (retrieved dynamically).
     * @param windowHeight Screen height in pixels (retrieved dynamically).
     * @return Pointer to the main Camera.
     *
     * Automatically sets up viewport and projection aspect ratio.
     */
    Camera* CreateMainCamera(int windowWidth, int windowHeight);

    /**
     * @brief Creates the main camera with a custom viewport/framebuffer/layer.
     * @param name Unique camera name (e.g., "MainCamera").
     * @param viewport glm::ivec4(x, y, width, height)
     * @param framebuffer Optional framebuffer ID (0 = default)
     * @param layer Render layer this camera draws from
     */
    Camera* CreateMainCamera(const std::string& name,
        const glm::ivec4& viewport,
        unsigned int framebuffer = 0,
        int layer = 0);

    Camera* GetMainCamera() const { return mainCamera; }

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
    const std::vector<CameraRenderData>& GetActiveCameras() const { return activeCameras; }

    /**
    * @brief Returns first active camera for this frame.
    */
    Camera& GetActive() const;
};