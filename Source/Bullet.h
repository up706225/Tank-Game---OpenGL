#ifndef BULLET_H_
#define BULLET_H_

class bulletInfo //creates the bullet class 
{
	public:
		bulletInfo();

		float startTime; //time bullet was created
		float bulletLife; //bullets total time in world

		float xPos; //bullets x position
		float yPos; //bullets y position

		float bulletWidth; //bullets width
		float bulletHeight; //bullets height

		float xSpeed; //xspeed
		float ySpeed; //yspeed

		float bulletRotation; //rotation bullet is traveling on
};

#endif /* BULLET_H_ */