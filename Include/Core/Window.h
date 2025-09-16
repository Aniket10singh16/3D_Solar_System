/**
@file Window.h
@brief Wrapper around GLFW window creation and OpenGL context.

The Window class is responsible for:
	Initializing GLFW and creating an OpenGL context.
	Managing the application window (size, title, close events).
	Handling buffer swaps and event polling.

By abstracting GLFW behind this class, the engine remains modular.
If you later switch to SDL or another API, only Window.cpp changes.
*/
#pragma once
#include <string>
#include <glm/glm.hpp>
struct GLFWwindow;


/**
 * @class Window
 * @brief Encapsulates GLFW window and OpenGL context lifecycle.
 *
 * Provides a simple interface for creating and managing a rendering window.
 * Other subsystems (Renderer, Input) interact with Window but don’t touch GLFW directly.
 */

class Window
{
private:
	GLFWwindow* handle_ = nullptr;	///< Raw GLFW window handle
	int width_;						///< Width in pixels
	int height_;					///< Height in pixels
	std::string title_;				///< Window title string

public:
/**
 * @brief Constructs a Window object with given dimensions and title.
 * @param w Width of the window in pixels.
 * @param h Height of the window in pixels.
 * @param title Title bar text.
 */
	Window(int w, int h, const std::string& title);

	/// Releses GLFW resources when the window is deplyed .
	~Window();


	/**
	* @brief Initializes GLFW, creates window, and loads GLAD.
	* @return True if initialization succeeded, false otherwise.
	*/
	bool Initialize();

	/// Polls for input and window events (non-blocking).
	void PollEvents() const;

	/// Swaps front/back buffers to present the rendered frame.
	void SwapBuffers() const;

	/// Checks if the window should close
	bool ShouldClose() const;

	/// Gets the current window size as a glm::ivec2.
	glm::ivec2 GetSize() const;

	//Chnages the window title string.
	void SetTitle(const std::string& newTitle);

	/// Provides access to the underlying GLFW handle
	GLFWwindow* GetNativeHandle() const { return handle_; };
};
