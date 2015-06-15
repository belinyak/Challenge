#ifndef CHALLENGE_CAMERA_HPP
#define CHALLENGE_CAMERA_HPP

#include <Source\Transform.hpp>

namespace Challenge
{

enum class ProjectionType
{
	Perspective,
	Orthographic,
};

struct Camera
{
	Camera();
	Camera(const Camera& _other) = default;

	void lookAt(const Vector3& _position, const Vector3& _up = {0,1,0});

	void offsetOrientation(const Radian& _yaw, const Radian& _pitch);

	Vector3 forward() const;
	Vector3 backward() const;
	Vector3 right() const;
	Vector3 left() const;
	Vector3 up() const;
	Vector3 down() const;

	Matrix4 getMatrix() const;
	Matrix4 getProjection() const;
	Matrix4 getView() const;

	Transform transform;
	Radian fieldofView;
	float orthoScale ;
	float nearPlane;
	float farPlane;
	float viewportaspectRatio;
	ProjectionType projectiontype;
};

} // !namespace Challenge
#endif // !#define CHALLENGE_CAMERA_HPP

