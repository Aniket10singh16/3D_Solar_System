/**
 * @file CameraController.h
 * @brief Declares the CameraController class for mapping input → camera updates.
 *
 * The CameraController is the "brain":
 *  - Reads input state (keyboard/mouse) via Input system
 *  - Translates input into movement and rotation commands
 *  - Calls Camera.Move / Camera.Rotate appropriately
 *
 * This design keeps Camera clean and reusable,
 * while CameraController encapsulates user-control logic.
 */

#pragma once
#include "Core/Input.h"
#include "Scene/Camera.h"

class CameraController
{
private:
	Camera& camera;			///< Reference to controlled camera
	float movementSpeed = 5.0f;	///< Units per second
	float mouseSensitivity = 0.05f;	///< Degrees per pixel of mouse movement

public:
    /**
     * @brief Constructs a CameraController that manipulates a Camera.
     * @param cam Reference to a Camera object (stored in CameraManager).
     */
    CameraController(Camera& cam);

    /**
     * @brief Updates the camera based on current input state.
     * @param deltaTime Time elapsed since last frame (seconds).
     *
     * Behavior:
     * - WASD: Move camera forward/back/left/right
     * - Mouse: Rotate yaw/pitch for looking around
     */
    void Update(float deltaTime);
};
