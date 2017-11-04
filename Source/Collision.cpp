#include "GameInfo.h" 
// is the 2d point (px,py) inside the 2d rotated bounding box (assumes box is 2-way symmetrical and centred on bx and by)
bool isCollision(float px, float py, float bx, float by, float bWidth,  float bHeight, float bAngle)
{
	// convert angle to radians...
	//bAngle *= DEGTORAD;

	// "de-rotate" point...
	float newX = bx + (px-bx) * cos(-bAngle) - (py-by) * sin(-bAngle);
	float newY = by + (px-bx) * sin(-bAngle) + (py-by) * cos(-bAngle);

	// check if it would be inside a "straight" version of the bounding box...
	if ((newX >= (bx - (bWidth))) && (newX <= (bx + (bWidth))) && (newY >= (by - (bHeight))) && (newY <= (by + (bHeight))))
	{
		return true;
	}
	else 
	{ 
		return false; 
	}
 
}

