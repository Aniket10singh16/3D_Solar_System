/**
 * @file CameraManager.cpp
 * @brief Implements the multi-camera management system.
 */

#include "Scene/CameraManager.h"

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
}

void CameraManager::SetActive(const std::string& name, bool active)
{
	auto it = cameras.find(name);
	if (it == cameras.end())
		throw std::runtime_error("CameraManager: Camera not found: " + name);

	it->second.active = active;
}

CameraRenderData& CameraManager::GetCameraData(const std::string& name)
{ 
	auto it = cameras.find(name);
	if (it == cameras.end())
		throw std::runtime_error("CameraManager: Camera not found: " + name);

	return it->second;
}

std::vector<CameraRenderData> CameraManager::GetActiveCameras() const
{
	std::vector<CameraRenderData> activeList;
	for (const auto& [name, data] : cameras)
		if (data.active && data.camera)
			activeList.push_back(data);

	return activeList;
}

Camera& CameraManager::GetActive() const
{
    for (const auto& [name, data] : cameras)
        if (data.active && data.camera)
            return *data.camera;
    throw std::runtime_error("CameraManager: No active camera found.");
}