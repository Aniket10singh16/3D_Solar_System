/**

@file Application.h

@brief Core entry point for the Celestial Engine runtime.

The Application class owns the main loop, initializes subsystems,

and orchestrates rendering. It ties together Window, Input,

Renderer, and (eventually) Scene and GameObjects.
*/
#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <memory>
#include <string>
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Core/Input.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include <GLFW/glfw3.h>
#include "Scene/CameraManager.h"
#include "Scene/CameraController.h"
#include <iostream>

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
    std::unique_ptr<Window> window;    ///< Window and OpenGL context
    std::unique_ptr<Renderer> renderer; ///< Renderer for issuing draw calls
    std::unique_ptr<CameraManager> cameraManager; ///< Stores and switches between cameras
    std::unique_ptr<CameraController> cameraController; ///< Controls the active camera (owned externally)

    // Planet objects
    RenderObject sun;
    RenderObject earth;
    RenderObject moon;

    bool running = true;    ///< Loop condition

    void InitScene();
    void ProcessInput(float dt); ///< Handle global input
    void Update(float dt);
    void Render();       

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

