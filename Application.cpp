#include "Application.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title)
    : window(width, height, title)
{
}

void Application::Run()
{
    // --- 1. Initialize subsystems ---
    if (!window.Initialize()) {
        std::cerr << "[Application] Failed to initialize Window\n";
        return;
    }

    Input::Initialize(window.GetNativeHandle());
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
    while (!window.ShouldClose()) {
        // Poll for keyboard/mouse input
        window.PollEvents();

        // Clear the screen with dark gray
        renderer.Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

        // Draw the triangle
        renderer.Draw(triangle, shader);

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
