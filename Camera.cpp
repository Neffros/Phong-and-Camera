#include <Camera.h>

void Camera::setForward(myVector3 pos)
{

	forward = pos;

}

void Camera::setRight(myVector3 pos)
{
	right = pos;
}

void Camera::setUp(myVector3 pos)
{
	up = pos;
}

void Camera::setPosition(myVector3 pos)
{
	position = pos;
}

myVector3 Camera::getForward()
{
	return forward;
}

myVector3 Camera::getUp()
{
	return up;
}

myVector3 Camera::getRight()
{
	return right;
}

myVector3 Camera::getPosition()
{
	return position;
}

Camera::Camera()
{

}

float* Camera::lookAt(myVector3 target)
{
	myVector3 upWorld(0, 1, 0);
	forward = (position - target).normalize();
	right = upWorld.cross(forward).normalize();
	up = forward.cross(right).normalize();

	float matrixView[] = {
		right.getX(), right.getY(), right.getZ(), -right.getX() * position.getX() - right.getY() * position.getY() - right.getZ() * position.getZ(),
		up.getX(), up.getY(), up.getZ(), -up.getX() * position.getX() - up.getY() * position.getY() - up.getZ() * position.getZ(),
		forward.getX(), forward.getY(), forward.getZ(), -forward.getX() * position.getX() - forward.getY() * position.getY() - forward.getZ() * position.getZ(),
		0,0,0,1
	};

	/*float matrixView[] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};*/

	return matrixView;
	//setForward();
}
