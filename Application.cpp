#include "Application.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title)
    : window(width, height, title)
{
    // Register window with input system
    Input::Initialize(window.GetNativeHandle());

    // Create cameras
    Camera* mainCamera = new Camera({ 0, 0, 3 }, (float)width / height);
    Camera* overheadCamera = new Camera({ 0, 50, 0 }, (float)width / height);

    // Example viewport: full window (x=0, y=0, width, height)
    glm::ivec4 mainViewport(0, 0, width, height);
    glm::ivec4 overheadViewport(width - 256, height - 256, 256, 256);

    cameraManager.AddCamera("main", mainCamera, mainViewport);
    cameraManager.AddCamera("overhead", overheadCamera, overheadViewport);

}

Application::~Application()
{
    delete &cameraManager;
    delete controller;
}

void Application::ProcessInput()
{
    // Global escape condition
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        running = false;
    }
}

void Application::Run()
{
    // --- 1. Initialize subsystems ---
    if (!window.Initialize()) {
        std::cerr << "[Application] Failed to initialize Window\n";
        return;
    }

    //Input::Initialize(window.GetNativeHandle());
    renderer.Initialize();


    // --- 2. Setup Phase 1 demo objects ---
    std::vector<Vertex> vertices = {
        {{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // Top (red)
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Left (green)
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}  // Right (blue)
    };
    Mesh triangle(vertices);

    std::string vs = R"(
        #version 450 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        out vec3 ourColor;
        void main() {
            gl_Position = vec4(aPos, 1.0);
            ourColor = aColor;
        }
    )";

    std::string fs = R"(
        #version 450 core
        in vec3 ourColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(ourColor, 1.0);
        }
    )";

    Shader shader(vs, fs);

    // --- 3. Main loop ---
    while (running && !window.ShouldClose()) {
        // Time tracking
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Poll for keyboard/mouse input
        window.PollEvents();

        ProcessInput();

        // Update active camera via controller
        controller->Update(deltaTime);

        // Clear the screen with dark gray
        renderer.Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

        // Draw the triangle
        //renderer.Draw(triangle, shader);
        auto activeCameras = cameraManager.GetActiveCameras();
        renderer.RenderFrame(activeCameras);


        // Swap front/back buffers
        window.SwapBuffers();

        // Escape key closes the window
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            break;
        }
    }

    // --- 4. Shutdown ---
    std::cout << "[Application] Shutting down cleanly\n";
}
