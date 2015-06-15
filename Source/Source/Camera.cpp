#include <Source\Camera.hpp>

namespace Challenge
{
Camera::Camera()
	: transform()
	, fieldofView(Degree(50))
	, orthoScale(1.0f)
	, nearPlane(0.1f)
	, farPlane(256.0f)
	, viewportaspectRatio(4.0f / 3.0f)
	, projectiontype(ProjectionType::Perspective)
{}

void Camera::lookAt(const Vector3& _position, const Vector3& _up)
{
	const Vector3& pos = transform.position;

	if (length(pos - _position) <= 0.001f)
		return; //cannot look at where you are!

	if (fabs(dot(pos, { 0, 1, 0 }) - 1.0f) <= 0.001f)
	{
		std::cerr << "Camera::lookAt - viewDirection and Up vector are colinear.\n";
		return;
	}

	Matrix4 mat = Challenge::lookAt(pos, _position, _up);

	transform.orientation = matrix4ToQuaternion(mat);
}

void Camera::offsetOrientation(const Radian& _yaw, const Radian& _pitch)
{

}

Vector3 Camera::forward() const {
	return(transform.orientation * Vector3(0, 0, -1));
}
Vector3 Camera::backward() const {
	return(transform.orientation * Vector3(0, 0, 1));
}

Vector3 Camera::right() const {
	return(transform.orientation * Vector3(1, 0, 0));
}
Vector3 Camera::left() const {
	return(transform.orientation * Vector3(-1, 0, 0));
}

Vector3 Camera::up() const {
	return(transform.orientation * Vector3(0, 1, 0));
}
Vector3 Camera::down() const {
	return(transform.orientation * Vector3(0, -1, 0));
}

Matrix4 Camera::getMatrix() const {
	return( getProjection() * getView());
}
Matrix4 Camera::getProjection() const
{
	Matrix4 proj;

	if (projectiontype == ProjectionType::Perspective) {
		proj = perspective(this->fieldofView,viewportaspectRatio,nearPlane,farPlane);
	}
	else if (projectiontype == ProjectionType::Orthographic)
	{
		float distance = 0.5f * (farPlane - nearPlane);
		proj = ortho(-orthoScale * viewportaspectRatio, orthoScale * viewportaspectRatio,
						 -orthoScale,orthoScale,
						 -distance, distance);
	}
	return(proj);
}
Matrix4 Camera::getView() const
{
	Matrix4 view;
	view = scale(Vector3(1)/transform.scale)* quaternionToMatrix4(transform.orientation) * translate(-transform.position);
	return(view);
}

} // !namespace Challenge