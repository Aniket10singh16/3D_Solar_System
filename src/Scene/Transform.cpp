/**
 * @file Transform.cpp
 * @brief Transform implementation: model matrix, normal matrix, and helpers.
 *
 * Detailed math reminders:
 *  - Translation matrix T (4x4) moves points: T * (x,y,z,1) -> (x+tx, y+ty, z+tz, 1)
 *  - Scale matrix S (4x4) scales axes: diag(sx, sy, sz, 1)
 *  - Rotation matrix R (4x4) is derived from a quaternion q. Quaternion -> 3x3 rotation,
 *    then promoted to 4x4 for homogeneous coords.
 *  - Final model matrix M = T * R * S. This means scale happens in object-local
 *    axes, then rotate around origin, then translate into world.
 *
 * Normal matrix:
 *  - When non-uniform scale exists, normals must be transformed by the inverse-transpose
 *    of the 3x3 linear part of the model matrix:
 *      N = inverse(transpose(mat3(M)))
 *  - Using this ensures normal vectors remain perpendicular to surfaces after transform.
 */
#include "Scene/Transform.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"	// for glm::toMat4
#include "glm/gtc/matrix_inverse.hpp" // for invereTranspose if needed


Transform::Transform()
	: position(0.0f, 0.0f, 0.0f),
	rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),	// identity quat (w=1)
	scale(1.0f, 1.0f, 1.0f),
	dirty(true)
{

}

Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scl)
	: position(pos), rotation(rot), scale(scl), dirty(true)
{

}

void Transform::RecalculateIfNeeded() const
{
	if (!dirty) return;

	// 1) Scale matrix (4x4)
	glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);

	// 2) Rotation matrix from quaternion (4x4)
	//	glm::toMat4 creates a 4x4 rotation matrix from quaternion.
	glm::mat4 R = glm::toMat4(rotation);

	// 3) Translation matrix
	glm::mat4 T = glm::translate(glm::mat4(1.0f), position);

	// Model matrix: M = T * R * S
	// Note: column-major multiplication ensures scale then rotation then translation
	modelMatrixCache = T * R * S;

	// Normal matrix = inverse(transpose(mat3(M)))
	// Convert modelMatrixCahce to 3x3 linear part and compute inverse-transpose.
	glm::mat3 linearPart = glm::mat3(modelMatrixCache);
	// Use glm::inverse and transpose to produce normal transform
	normalMatricCahe = glm::inverse(glm::transpose(linearPart));

	dirty = false;
}

glm::mat4 Transform::GetModelMatrix() const
{
	RecalculateIfNeeded();
	return modelMatrixCache;
}

glm::mat3 Transform::GetNormalMatrix() const
{
	RecalculateIfNeeded();
	return normalMatricCahe;
}

// --- Position / translation ---
void Transform::SetPosition(const glm::vec3& pos)
{
	position = pos;
	dirty = true;
}

void Transform::Translate(const glm::vec3& delta)
{
	position += delta;
	dirty = true;
}

void Transform::SetRotation(const glm::quat& quat)
{
	rotation = glm::normalize(quat);	// keep quaternion normalized
	dirty = true;
}

void Transform::SetRotationEuler(const glm::vec3& eularDegrees)
{
	// glm expects radians; convert and construct quaternion from Euler (yaw, pitch, roll)
	glm::vec3 radians = glm::radians(eularDegrees);
	// We will treat the Euler order as (pitch, yaw, roll) or commonly (X = pitch, Y = yaw, Z = roll)
	// A safe approach is to build from yaw/pitch/roll explicitly:
	glm::quat qpitch = glm::angleAxis(radians.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat qYaw = glm::angleAxis(radians.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat qRoll = glm::angleAxis(radians.z, glm::vec3(0.0f, 0.0f, 1.0f));
	// Compose: q = yaw * pitch * roll (order matters - choose a convention be consistant)
	rotation = glm::normalize(qYaw * qpitch * qRoll);
	dirty = true;
}   

void Transform::RotateEuler(const glm::vec3& eularDeltaDegrees)
{
	glm::vec3 radians = glm::radians(eularDeltaDegrees);
	glm::quat dq = glm::quat(glm::vec3(radians.x, radians.y, radians.z));	// glm::quat accepts Euler in radians as ctor (pitch,yaw,roll)
	rotation = glm::normalize(dq * rotation); // apply delta before current orientation
	dirty = true;
}

void Transform::RotateAxisAngle(const glm::vec3& axis, float angleDegrees)
{
	float rad = glm::radians(angleDegrees);
	glm::quat dq = glm::angleAxis(rad, glm::normalize(axis));
	rotation = glm::normalize(dq * rotation);
	dirty = true;
}

void Transform::RotateByQuat(const glm::quat& delta)
{
	rotation = glm::normalize(delta * rotation);
	dirty = true;
}

// --- Scale ---
void Transform::SetScale(const glm::vec3& scl)
{
	scale = scl;
	dirty = true;
}

void Transform::ScaleBy(const glm::vec3& factor)
{
	scale *= factor;
	dirty = true;
}

// --- Direction helpers (world-space)
glm::vec3 Transform::Forward() const
{
	// Local forward is nagetive z in OpenGL conventions
	// Transform local forward (0, 0, -1) by rotation only (ignore scale/translation)
	return glm::normalize(rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Transform::Up() const
{
	return glm::normalize(rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Transform::Right() const
{
	return glm::normalize(rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

void Transform::LookAt(const glm::vec3& target, const glm::vec3& up)
{
	// Compute direction from position -> target
	glm::vec3 forwardDir = glm::normalize(target - position);

	//Handle degenerate case (target position)
	if (glm::length(forwardDir) < 1e-6f)
		return;

	// glm::l0okAt generates a view matrix (camrea space),
	// so we invert it to get the world-space rotation matrix.
	glm::mat4 view = glm::lookAt(position, target, up);
	glm::mat4 rotationMatrix = glm::mat3(glm::transpose(view));	// inverse(view) = transpose for rotation

	// Convert to quaternion
	rotation = glm::normalize(glm::normalize(glm::quat_cast(rotationMatrix)));
	dirty = true;
}