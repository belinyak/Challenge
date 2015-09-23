#ifndef CHALLENGE_CAMERA_H
#define CHALLENGE_CAMERA_H

#include <Math\Transform.h>

struct Camera
{ 
    Camera();
    Camera(const Camera& _other) = default;

    Vector3 forward() const;
    Vector3 backward() const;
    Vector3 right() const;
    Vector3 left() const;
    Vector3 up() const;
    Vector3 down() const;

    Matrix4 getMatrix() const; 
   
    void lookAt(const Vector3& _position, const Vector3& _up = {0,1,0});

    void FollowHero(Vector3 guyPosition)
    {
	transform.position.x = guyPosition.x;
	transform.position.y = guyPosition.y;
    }

    
    Transform transform;
    float fieldofView;
    float nearPlane;
    float farPlane;
    float viewportaspectRatio;
};

#endif // !#define CHALLENGE_CAMERA_H

