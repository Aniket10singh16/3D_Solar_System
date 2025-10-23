/**
 * @file Transform.h
 * @brief Transform component: position, rotation (quat), scale and model matrix math.
 *
 * This Transform class is intended to be a small value-type component that:
 *  - Stores local position, rotation and scale
 *  - Produces the Model matrix used to transform object-space vertices into world-space
 *  - Provides utility functions to move / rotate / scale the transform
 *
 * Mathematical notes:
 *  - Model matrix M = T * R * S
 *      T = translation matrix
 *      R = rotation matrix (from quaternion)
 *      S = scale matrix
 *  - We use column-major matrices (GLM default) and the convention that
 *      vertex_world = M * vertex_local
 *
 * Implementation notes:
 *  - Rotation is stored as a glm::quat for stable composition and interpolation
 *  - Euler helpers convert to/from quaternion for convenience
 *  - Normal matrix (for transforming normals) is provided: inverse(transpose(model))
 */

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
private:
	glm::vec3 position;	///< Translation in world units
	glm::quat rotation;	///< Orientation stored as quaternion
	glm::vec3 scale;	///< Non-uniform scale per axis

	mutable bool dirty;		///< Whether cahced matrices need recomputing
	mutable glm::mat4 modelMatrixCache;
	mutable glm::mat4 normalMatricCahe;

	/**
	* @brief Recalculates cached matrices (model + normal) if dirty.
	* Marked mutable so const getters can compute on demand
	*/
	void RecalculateIfNeeded() const;

public:
	/** @brief Default constructor: identity transform at origin. */
	Transform();

	/** @brief Construct with explicit components. */
	Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scl);

	glm::vec3 GetPosition() const { return position; }
	glm::quat GetRotation() const { return rotation; }
	glm::vec3 GetScale() const { return scale; }

	/**
	  * @brief Returns the Model (M) matrix: transforms local coords -> world coords.
	  * M = T * R * S
	  */

	glm::mat4 GetModelMatrix() const;

	/**
	 * @brief Returns the 3x3 normal matrix = inverse(transpose( mat3(model) ))
	 * This is used to correctly transform normals under non-uniform scale.
	 */
	glm::mat3 GetNormalMatrix() const;

	// ---------------------------
	// Setters & modifiers
	// ---------------------------

	void SetPosition(const glm::vec3& pos);
	void Translate(const glm::vec3& delta);

	/** set rotation directly with a quaternion. */
	void SetRotation(const glm::quat& quat);

	/** Set rotation from Euler angles (degrees). */
	void SetRotationEuler(const glm::vec3& eulerDegrees);

	/** Rotate by an Euler delta (degrees). */
	void RotateEuler(const glm::vec3& eulerDeltaDegrees);

	/** Rotate by an axis-angle (axis normalized, angle degrees). */
	void RotateAxisAngle(const glm::vec3& axis, float angleDegrees);

	/** Rotate by a quaternion delta (qNew = delta * qOld). */
	void RotateByQuat(const glm::quat& delta);

	void SetScale(const glm::vec3& scl);
	void ScaleBy(const glm::vec3& factor);


	// ---------------------------
	// Convenience direction vectors (in world-space)
	// ---------------------------
/** @return Forward direction (local -Z) in world space. */
	glm::vec3 Forward() const;

	/** @return Up direction (local +Y) in world space. */
	glm::vec3 Up() const;

	/** @return Right direction (local +X) in world space. */
	glm::vec3 Right() const;

	/**
	 * @brief Orients this transform so its forward direction points toward a target point.
	 * @param target World-space position to look at.
	 * @param up World-space "up" vector (default = +Y).
	 *
	 * Mathematical note:
	 *  - Uses glm::lookAt() inverted (since glm::lookAt builds a view matrix).
	 *  - Converts the resulting rotation from matrix to quaternion.
	 */
	void LookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0));
};
