#include "Application.h"

Application::Application(int width, int height, const std::string& title)
{
    // Initialize the window and OpenGL context
    window = std::make_unique<Window>(width, height, "Solar System");

    // Initialize the GLFW window, OpenGL context and GLAD inside Window::Initialize()
    if (!window->Initialize()) {
        throw std::runtime_error("Failed to initialize Window.");
    }

    glfwMakeContextCurrent(window->GetNativeHandle());

    // Register window with input system
    Input::Initialize(window->GetNativeHandle());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD.");

    // Initialize systems
    renderer = std::make_unique<Renderer>();
    cameraManager = std::make_unique<CameraManager>();
    cameraController = std::make_unique<CameraController>(*cameraManager->CreateMainCamera(width, height));

    // Initialize the scene
    InitScene();

    std::cout << "[Application] Initialized successfully.\n";

}


Application::~Application()
{
    glfwTerminate();
}

void Application::InitScene()
{
    // 3D sphere meshes
    sun.mesh = Mesh::CreateSphere(2.0f, 48, 24);
    earth.mesh = Mesh::CreateSphere(1.0f, 36, 18);
    moon.mesh = Mesh::CreateSphere(0.5f, 24, 12);

    // Transform setup - place objects in front of camera (negative Z direction from camera at +Z)
    // Camera at (0, 0, 15) looking at negative Z, so objects should be at Z < 15
    sun.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    earth.transform.SetPosition(glm::vec3(6.0f, 0.0f, 0.0f));
    moon.transform.SetPosition(glm::vec3(8.0f, 0.0f, 0.0f));

    sun.renderLayer = earth.renderLayer = moon.renderLayer = 0;
    
    std::cout << "[InitScene] Created 3 spheres (sun, earth, moon)\n";
    std::cout << "[InitScene] Sun at (0, 0, 0), Earth at (6, 0, 0), Moon at (8, 0, 0)\n";
}

void Application::ProcessInput(float dt)
{
    cameraController->Update(dt);
    // Global escape condition
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        running = false;
    }
}

void Application::Update(float dt)
{
    // Simple orbital motion for Earth & Moon
    static float angle = 0.0f;
    angle += dt * 20.0f; // degrees per second

    float radians = glm::radians(angle);

    earth.transform.SetPosition(glm::vec3(6.0f * cos(radians), 0.0f, 6.0f * sin(radians)));
    moon.transform.SetPosition(earth.transform.GetPosition() + 
        glm::vec3(2.0f * cos(3 * radians), 0.0f, 2.0f * sin(3 * radians)));
}

void Application::Render()
{
    // Add objects to renderer each frame
    renderer->AddRenderObject(sun);
    renderer->AddRenderObject(earth);
    renderer->AddRenderObject(moon);

    // Render from all active cameras
    auto activeCameras = cameraManager->GetActiveCameras();
    renderer->RenderFrame(activeCameras);

    // Clear object list
    renderer->ResetSceneObjects();

    // Swap buffers
    window->SwapBuffers();
}

void Application::Run()
{
    float lastTime = static_cast<float>(glfwGetTime());

    //Input::Initialize(window.GetNativeHandle());
    renderer->Initialize();


    // --- 3. Main loop ---
    while (running && !window->ShouldClose())
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        ProcessInput(deltaTime);
        Update(deltaTime);
        Render();
    }

    // --- 4. Shutdown ---
    std::cout << "[Application] Shutting down cleanly\n";
}
