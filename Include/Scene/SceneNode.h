/**
 * @file SceneNode.h
 * @brief Basic scene graph node that holds a Transform and supports hierarchy.
 *
 * The SceneNode class allows parent-child relationships between objects.
 * Each node maintains its own local Transform, and computes its world transform
 * by multiplying the parent’s world matrix.
 *
 * Mathematical relation:
 *   M_world = M_parent * M_local
 *
 * This allows for hierarchical animation, such as:
 *   Sun (root)
 *     └── Earth (rotates/orbits Sun)
 *           └── Moon (rotates/orbits Earth)
 */
#pragma once
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "Scene/Transform.h"

class SceneNode
{
private:
	std::string name;
	Transform localTransform;
	SceneNode* parent = nullptr;
	std::vector<std::unique_ptr<SceneNode>> children;

public:
	SceneNode(const std::string& nodeName = "Node");

	Transform& GetTransform() { return localTransform; }
	const Transform& GetTransform() const { return localTransform; }

	void SetParent(SceneNode* newParent);
	SceneNode* GetParent() const { return parent; }

	SceneNode* CreateChild(const std::string& childName);

    /**
     * @brief Computes this node’s world transform recursively.
     * @return World transform matrix (Model matrix in world space).
     */
    glm::mat4 GetWorldMatrix() const;

    /**
     * @brief Returns the world-space position of this node.
     */
    glm::vec3 GetWorldPosition() const;

    /**
     * @brief Updates or animates node logic (overridable).
     * For now, does nothing — extend for simulation.
     */
    virtual void Update(float deltaTime);

    /**
     * @brief Calls Update recursively for this node and all children.
     */
    void UpdateHierarchy(float deltaTime);
};
