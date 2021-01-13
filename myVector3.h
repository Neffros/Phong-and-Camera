#pragma once

class myVector3
{

	private:
		float x;
		float y;
		float z;
	public:
		myVector3(float x=0, float y=0, float z=0);
		myVector3 normalize();
		float calculateNorm();
		float getX();
		float getY();
		float getZ();
		void setX(float newX);
		void setY(float newY);
		void setZ(float newZ);
		myVector3 cross(myVector3 vec2);
		myVector3& operator + (myVector3 vec)
		{
			//m_rows.swap(m.m_rows)	 	 	 	 		  		 	  
			//swap(m);	 	 	 	 		  		 	  
			return *this;
		}
		myVector3 operator+(const myVector3& vec2) const;
		myVector3 operator-(const myVector3& vec2) const;
};
