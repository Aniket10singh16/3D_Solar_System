/**
 * @file CameraManager.cpp
 * @brief Implements the multi-camera management system.
 */

#include "Scene/CameraManager.h"
#include <iostream>

// ----------------------------------------------------
// Destructor - Clean up allocated camera
// ----------------------------------------------------
CameraManager::~CameraManager()
{
	if (mainCamera)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
}

// ----------------------------------------------------
// Auto-create main camera using screen resolution
// ----------------------------------------------------
Camera* CameraManager::CreateMainCamera(int windowWidth, int windowHeight)
{
	// Compute aspect ratio dynamically
	float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

	// Create the camera instance - position it to view the solar system centered
	// Slightly elevated and back for a good overview of the orbiting system
	mainCamera = new Camera({ 0, 3, 20 }, aspectRatio);
	glm::ivec4 mainViewport(0, 0, windowWidth, windowHeight);

	// Configure projection using aspect ratio
	//cam->SetPerspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);

	// Register with manager
	glm::ivec4 viewport(0, 0, windowWidth, windowHeight);
	AddCamera("MainCamera", mainCamera, mainViewport, 0, 0);

	std::cout << "[CameraManager] Main camera created (auto aspect ratio: " << aspectRatio << ")\n";
	return mainCamera;
}


Camera* CameraManager::CreateMainCamera(const std::string& name, const glm::ivec4& viewport,
	unsigned int framebuffer, int layer)
{
	// Compute aspect ratio dynamically
	float aspectRatio = static_cast<float>(viewport.z) / static_cast<float>(viewport.w);

	// Create the camera instance
	mainCamera = new Camera({ 0, 0, 3 }, aspectRatio);

	// Configure projection using aspect ratio
	//cam->SetPerspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);

	// Register with manager
	AddCamera("MainCamera", mainCamera, viewport, framebuffer, layer);

	std::cout << "[CameraManager] Main camera created (auto aspect ratio: " << aspectRatio << ")\n";
	return mainCamera;
}


void CameraManager::AddCamera(const std::string& name, Camera* camera,
	const glm::ivec4& viewport, unsigned int framebuffer, int layer)
{
	CameraRenderData data;
	data.name = name;
	data.camera = camera;
	data.viewport = viewport;
	data.framebuffer = framebuffer;
	data.renderLayer = layer;
	data.active = true;

	cameras[name] = data;
	activeCameras.push_back(data);
}

void CameraManager::SetActive(const std::string& name, bool active)
{
	auto it = cameras.find(name);
	if (it == cameras.end())
		throw std::runtime_error("CameraManager: Camera not found: " + name);

	it->second.active = active;

	// Find existing entry in activeCameras by name
	auto vecIt = std::find_if(activeCameras.begin(), activeCameras.end(),
		[&name](const CameraRenderData& d) { return d.name == name; });

	if (!active)
	{
		// Remove from activeCameras only if it exists
		if (vecIt != activeCameras.end())
			activeCameras.erase(vecIt);
	}
	else
	{
		// If already present, update the stored data to keep it in sync
		if (vecIt != activeCameras.end())
		{
			*vecIt = it->second;
		}
		else
		{
			// Add to activeCameras only if it does not already exist
			activeCameras.push_back(it->second);
		}
	}
}

CameraRenderData& CameraManager::GetCameraData(const std::string& name)
{ 
	auto it = cameras.find(name);
	if (it == cameras.end())
		throw std::runtime_error("CameraManager: Camera not found: " + name);

	return it->second;
}

Camera& CameraManager::GetActive() const
{
    for (const auto& [name, data] : cameras)
        if (data.active && data.camera)
            return *data.camera;
    throw std::runtime_error("CameraManager: No active camera found.");
}