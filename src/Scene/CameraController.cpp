/**
 * @file CameraController.cpp
 * @brief Implements CameraController: interprets input and updates Camera.
 */

#include "Scene/CameraController.h"
#include <GLFW/glfw3.h> // For key codes (GLFW_KEY_W, etc.)

CameraController::CameraController(Camera& cam)
	: camera(cam){ }

void CameraController::Update(float deltaTime)
{
	glm::vec3 moveDelta(0.0f);
	float velocity = movementSpeed * deltaTime;

	//WASD Movement
	if (Input::IsKeyPressed(GLFW_KEY_W))
		moveDelta += camera.GetFront() * velocity; // Forward

	if (Input::IsKeyPressed(GLFW_KEY_S))
		moveDelta -= camera.GetFront() * velocity; // Backward

	if (Input::IsKeyPressed(GLFW_KEY_A))
		moveDelta -= camera.GetRight() * velocity; // Left

	if (Input::IsKeyPressed(GLFW_KEY_D))
		moveDelta += camera.GetRight() * velocity; // Right

	camera.Move(moveDelta);

	// Mouse Look
	glm::dvec2 delta = Input::GetMouseDelta();
	camera.Rotate(static_cast<float>(delta.x) * mouseSensitivity,
		static_cast<float>(-delta.y) * mouseSensitivity);
}