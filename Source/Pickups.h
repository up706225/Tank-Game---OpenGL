#ifndef PICKUPS_H_
#define PICKUPS_H_

class powerUpInfo //creates the powerup class 
{
	public:
		powerUpInfo();

		float startTime; //time pickups was created
	
		float xPos; //pickups x position
		float yPos; //pickups y position

		float powerUpWidth; //pickups width
		float powerUpHeight; //pickups height
		
		bool visible; //pickup visible
		int powerUpType; //pickups type
};

#endif /* PICKUPS_H_ */