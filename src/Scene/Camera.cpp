/**
 * @file Camera.cpp
 * @brief Implements the Camera class.
 */

#include "Scene/Camera.h"

Camera::Camera(glm::vec3 pos, float aspect)
	: position(pos), worldUp(0.0f, 1.0f, 0.0f),
	yaw(-90.0f), pitch(0.0f), // Default facing negative Z
	fov(45.0f), aspectRatio(aspect),
	nearPlane(0.1f), farPlane(100.0f)
{
	front = glm::vec3(0.0f, 0.0f, -1.0f); // Looking forward by default
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	// LookAt: tranforms world -> view space
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	// Perspective projection:
	// - fov controls zoom
	// - aspect ensures correct proportions
	// - near/far clip planes define depth range
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::Move(const glm::vec3& delta)
{
	position += delta; // Translate in world space
}

void Camera::Rotate(float yawDelta, float pitchDelta)
{
	yaw += yawDelta;
	pitch += pitchDelta;

	// clamp pithc to avoid flipping the camera upside down
	if (pitch > 89.0f) pitch = 89.0f;
	if (yaw < -89.0f) yaw = -89.0f;

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	// Converts yaw & pitch (in degrees) to a normalized direction vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	// Recompute right and up to ensure orthogonality
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}