#include <cmath>
#include "myVector3.h"
myVector3 myVector3::normalize()
{
	float norm = calculateNorm();
	if (norm == 0)
		return *this;
	x = x / norm;
	y = y / norm;
	z = z / norm;
	return *this;
}
float myVector3::calculateNorm()
{
	return std::sqrtf(x * x + y * y + z * z);
}
float myVector3::getX()
{
	return x;
}
float myVector3::getY() 
{
	return y;
}
float myVector3::getZ()
{
	return z;
}
void myVector3::setX(float newX)
{
	x = newX;
}
void myVector3::setY(float newY)
{
	y = newY;
}
void myVector3::setZ(float newZ)
{
	z = newZ;
}
myVector3::myVector3(float newX, float newY, float newZ) :x(newX), y(newY), z(newZ)
{
	
}
myVector3 myVector3::operator+(const myVector3& vec2) const
{
	myVector3 result(0,0,0);
	result.x = this->x + vec2.x;
	result.y = this->y + vec2.y;
	result.z = this->z + vec2.z;

	return result;
}

myVector3 myVector3::cross(myVector3 vec2)
{
	myVector3 vec1(x,y,z);
	vec1.x = y * vec2.z - z * vec2.y;
	vec1.y = z * vec2.x - x * vec2.z;
	vec1.z = x * vec2.y - y * vec2.x;
	return vec1;
}
myVector3 myVector3::operator-(const myVector3& vec2) const
{
	myVector3 result(0, 0, 0);
	result.x = this->x - vec2.x;
	result.y = this->y - vec2.y;
	result.z = this->z - vec2.z;

	return result;
}