#include <Graphics\Camera.h>


Camera::Camera()
	: transform()
	, fieldofView(Radian(50)) //TODO
	, nearPlane(0.1f)
	, farPlane(256.0f)
	, viewportaspectRatio(4.0f / 3.0f) //NOTE(mate): "képernyõarány" ( 16:9 )
{}

void Camera::lookAt(const Vector3& _position, const Vector3& _up)
{
    const Vector3& pos = transform.position;

    if (length(pos - _position) <= 0.001f)
	return; //cannot look at where you are!

    Matrix4 mat = lookAtit(pos, _position, _up);
    transform.orientation = matrix4ToQuaternion(mat);
}

Vector3 Camera::forward() const
{
    return(conjugate(transform.orientation) * Vector3(0, 0, -1));
}
Vector3 Camera::backward() const
{
    return(conjugate(transform.orientation) * Vector3(0, 0, 1));
}
Vector3 Camera::right() const
{
    return(conjugate(transform.orientation) * Vector3(1, 0, 0));
}
Vector3 Camera::left() const
{
    return(conjugate(transform.orientation) * Vector3(-1, 0, 0));
}

Vector3 Camera::up() const
{
    return(conjugate(transform.orientation) * Vector3(0, 1, 0));
}
Vector3 Camera::down() const
{
    return(conjugate(transform.orientation) * Vector3(0, -1, 0));
}
//shadernek kell
Matrix4 Camera::getMatrix() const
{
	Matrix4 proj;

	proj = perspective(this->fieldofView, viewportaspectRatio, nearPlane, farPlane);
	Matrix4 view;
	view = scale(Vector3(1) / transform.scale)* quaternionToMatrix4(transform.orientation) * translate(-transform.position);
    return( proj * view);
}


