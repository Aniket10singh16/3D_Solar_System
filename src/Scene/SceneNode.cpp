#define GLM_ENABLE_EXPERIMENTAL

#include "Scene/SceneNode.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

SceneNode::SceneNode(const std::string& nodeName) : name(nodeName) {}

void SceneNode::SetParent(SceneNode* newParent) {
	parent = newParent;
}

SceneNode* SceneNode::CreateChild(const std::string& childName)
{
	children.push_back(std::make_unique<SceneNode>(childName));
	SceneNode* childPtr = children.back().get();
	childPtr->SetParent(this);
	return childPtr;
}

glm::mat4 SceneNode::GetWorldMatrix() const
{
	// Compute local model matrix
	glm::mat4 local = localTransform.GetModelMatrix();

	//Mulyiply by parent's world matrix if exists
	if (parent)
		return parent->GetWorldMatrix() * local;

	return local;
}

glm::vec3 SceneNode::GetWorldPosition() const
{
	glm::mat4 world = GetWorldMatrix();
	return glm::vec3(world[3]); // translation part
}

void SceneNode::Update(float deltTime)
{
	// Base class does nothing; can override for animation/orbit logic.
	(void)deltTime;
}

void SceneNode::UpdateHierarchy(float deltaTime)
{
	Update(deltaTime);
	for (auto& child : children)
		child->UpdateHierarchy(deltaTime);
}