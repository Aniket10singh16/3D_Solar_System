/**
 * @file Camera.h
 * @brief Declares the Camera class, which represents a single viewpoint in 3D space.
 *
 * A Camera provides:
 *  - A View Matrix: transforms world coordinates into the camera's local view space
 *  - A Projection Matrix: projects 3D points into 2D clip space for rendering
 *
 * This class is intentionally "dumb":
 *  - It stores position, orientation, and projection parameters
 *  - It exposes methods to move/rotate the camera
 *  - It does not know anything about input devices or key mappings
 *
 * Input logic is handled separately by CameraController.
 */
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    // Spatial properties
    glm::vec3 position;   ///< Camera position in world space
    glm::vec3 front;      ///< Direction the camera is facing
    glm::vec3 up;         ///< Local upward vector
    glm::vec3 right;      ///< Local rightward vector
    glm::vec3 worldUp;    ///< Fixed world-space up vector (usually (0,1,0))

    // Euler angles for orientation
    float yaw;            ///< Rotation around the vertical axis (left/right look)
    float pitch;          ///< Rotation around the horizontal axis (up/down look)

    // Projection parameters
    float fov;            ///< Field of view (in degrees)
    float aspectRatio;    ///< Aspect ratio (width / height of viewport)
    float nearPlane;      ///< Near clipping plane distance
    float farPlane;       ///< Far clipping plane distance

    /**
     * @brief Recalculates the orientation vectors (front, right, up)
     *        from the current yaw and pitch values.
     *
     * Mathematical breakdown:
     * - Converts spherical coordinates (yaw, pitch) into a forward direction vector.
     * - Ensures "right" and "up" are orthogonal via cross products.
     */
    void UpdateCameraVectors();

public:

    /**
     * @brief Constructs a camera at a given position with perspective projection.
     * @param pos Initial camera position in world space.
     * @param aspect Aspect ratio of the viewport (width / height).
     */
    Camera(glm::vec3 pos, float aspect);

    // @return View matrix: transform world space -> camera space
    glm::mat4 GetViewMatrix() const;

    //@return Projection Matrix: transform camera space -> clip space
    glm::mat4 GetProjectionMatrix() const;

    /**
     * @brief Moves the camera by a delta vector in world space.
     * @param delta Translation vector (world-space units).
     */
    void Move(const glm::vec3& delta);

    /**
     * @brief Rotates the camera by yaw/pitch deltas.
     * @param yawDelta Change in yaw (left/right, degrees).
     * @param pitchDelta Change in pitch (up/down, degrees).
     *
     * Keeps pitch clamped to avoid gimbal lock (±89°).
     */
    void Rotate(float yawDelta, float pitchDelta);

    //@return Currentn position
    glm::vec3 GetPosition() const { return position; }

    //@return Forward-facing vector
    glm::vec3 GetFront() const { return front; }

    /// @return Right-facing vector
    glm::vec3 GetRight() const { return right; }

    /// @return Upward vector
    glm::vec3 GetUp() const { return up; }
};