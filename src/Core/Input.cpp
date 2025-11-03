#include "Core/Input.h"
#include <GLFW/glfw3.h>

// Static member definitions
std::unordered_map<int, bool> Input::keyStates;
glm::dvec2 Input::mousePos(0.0);
glm::dvec2 Input::mouseDelta(0.0);

void Input::Initialize(GLFWwindow* window)
{
	// Install GLFW callbacks that forward events to Input's static methods
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	
	// Capture and hide the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Input::IsKeyPressed(int key)
{
	// Look up key state in the map (default false if not found)
	auto it = keyStates.find(key);
	return (it != keyStates.end()) ? it->second : false;
}

glm::dvec2 Input::GetMousePosition()
{
	return mousePos;
}

glm::dvec2 Input::GetMouseDelta()
{
	glm::dvec2 delta = mouseDelta;
	// Reset delta after reading to avoid accumulation
	mouseDelta = { 0.0, 0.0 };
	return delta;
}

void Input::KeyCallback(GLFWwindow*, int key, int, int action, int)
{
	// track key press/release state
	if (action == GLFW_PRESS)
	{
		keyStates[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyStates[key] = false;
	}
}

void Input::CursorPosCallback(GLFWwindow*, double xpos, double ypos)
{
	static bool firstMouse = true;
	
	// Initialize mouse position on first callback to avoid large delta
	if (firstMouse) {
		mousePos = { xpos, ypos };
		firstMouse = false;
		return;
	}
	
	// Update mouse delta (difference since last frame)
	mouseDelta = glm::dvec2(xpos, ypos) - mousePos;
	mousePos = { xpos, ypos };
}