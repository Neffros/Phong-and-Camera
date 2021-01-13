#pragma once
#include <myVector3.h>
class Camera
{
	private:
		myVector3 forward;
		myVector3 right;
		myVector3 up;
		myVector3 position;
	public:
		Camera();
		void setForward(myVector3 pos);
		void setRight(myVector3 pos);
		void setUp(myVector3 pos);
		void setPosition(myVector3 pos);
		myVector3 getForward();
		myVector3 getUp();
		myVector3 getRight();
		myVector3 getPosition();
		float* lookAt(myVector3 targetPos);

};