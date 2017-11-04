#include "GameInfo.h" 

//Function converts 'float a' from degrees to radian
float radianMath(float a)
	{
		float newRadian;
		newRadian = a * 3.14159265359f / 180;
		return  newRadian;
	}
//Function converts 'float a' from radian to degrees
	float angleMath(float a)
	{
		float newAngle;
		newAngle = a * 180 / 3.14159265359f;
		return  newAngle;
	}

	//Function works out the distance between two points
	float distanceMath(float a, float b, float x, float y)
	{
		return  sqrt((a - x)*(a - x) + (b - y)*(b - y)) ;
	}