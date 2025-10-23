/**

@file Application.h

@brief Core entry point for the Celestial Engine runtime.

The Application class owns the main loop, initializes subsystems,

and orchestrates rendering. It ties together Window, Input,

Renderer, and (eventually) Scene and GameObjects.
*/
#pragma once
#include <string>
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Core/Input.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include <GLFW/glfw3.h>
#include "Scene/CameraManager.h"
#include "Scene/CameraController.h"

/**
 * @class Application
 * @brief Manages engine lifecycle and main execution loop.
 *
 * Application is responsible for:
 * - Initializing core subsystems (Window, Input, Renderer).
 * - Creating test objects (triangle Mesh + Shader in Phase 1).
 * - Running the main loop until the window closes.
 */
class Application
{
private:
    Window window;    ///< Window and OpenGL context
    Renderer renderer; ///< Renderer for issuing draw calls
    CameraManager cameraManager; ///< Stores and switches between cameras
    CameraController* controller; ///< Controls the active camera (owned externally)

    bool running = true;    ///< Loop condition
    float deltaTime = 0.0f;     ///< Time between frames
    float lastFrame = 0.0f;   ///< Timestamp of last frame

    void ProcessInput();        ///< Handle global input

public:
    /**
     * @brief Constructs the Application with desired window parameters.
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param title Title for the window.
     */
    Application(int width, int height, const std::string& title);
    ~Application();

    /// Runs the main application loop (blocking until exit).
    void Run();
};

