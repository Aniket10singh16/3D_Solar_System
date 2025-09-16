/**

@file Input.h
@brief Static input manager wrapping GLFW callbacks.

The Input class centralizes input handling by:
	Installing GLFW callbacks for keyboard and mouse.
	Storing current key and mouse states in static variables.
	Providing high-level query methods (IsKeyPressed, GetMouseDelta).

This design decouples input from GLFW and makes it future-proof:
later you can add input mapping, record/replay, or swap backend APIs.
*/

#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
struct GLFWwindow;

/**
 * @class Input
 * @brief Static input manager for keyboard and mouse state.
 *
 * Provides an abstraction layer over GLFW input callbacks.
 * Other systems (e.g., CameraController, PlayerController)
 * can query input state without knowing about GLFW.
 */

class Input
{
private:
	static std::unordered_map<int, bool> keyStates;	///< Map of key → pressed/released
	static glm::dvec2 mousePos;	///< Current mouse position in window coords
	static glm::dvec2 mouseDelta; ///< Change in mouse position since last frame

public:
	/**
	 * @brief Installs input callbacks on the given GLFW window.
	 * @param window Pointer to GLFWwindow created by the Window class.
	 */
	static void Initialize(GLFWwindow* window);

	/**
	* @brief Returns whether a given key is currently pressed.
	* @param key GLFW keycode (e.g., GLFW_KEY_W).
	* @return True if the key is pressed.
	*/
	static bool IsKeyPressed(int key);

	/// @return Current mouse position in window coordinates (pixels).
	static glm::dvec2 GetMousePosition();

	/// @return Mouse movement delta since last frame.
	static glm::dvec2 GetMouseDelta();

	// ---------- GLFW Callback Hooks ----------

	/**
	 * @brief Callback for key events, installed on the GLFW window.
	 * @param window GLFW window handle.
	 * @param key Keyboard key (GLFW_KEY_*).
	 * @param scancode OS-specific scancode.
	 * @param action Press, release, or repeat.
	 * @param mods Modifier keys (shift, ctrl, etc.).
	 */
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/**
	 * @brief Callback for mouse movement, installed on the GLFW window.
	 * @param window GLFW window handle.
	 * @param xpos New x-coordinate of the mouse cursor.
	 * @param ypos New y-coordinate of the mouse cursor.
	 */
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
};