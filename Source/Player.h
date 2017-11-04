#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector> 
#include "Bullet.h"	
#include "Pickups.h"

// this class holds all of the information about a player
class playerInfo
{
	public:
		playerInfo();		// the constructor
		
		bool upPressed;		// forward (up key pushed)
		bool downPressed;	// reverse (down key pushed)
		bool leftPressed;	// turn left (left key pushed)
		bool rightPressed;  // turn right (rigght key pushed)

		bool turretLeft;	//turret left rotation (turret left key)
		bool turretRight;	//turret right rotation (turret right key)

		bool fireNormal;	//fire normal bullets (space bar pushed)
		bool fireSpecial;	//fire special bullets
		bool fireGrenade;	//fire grenade
		bool hasSpecial;	//has special?
		bool hasGrenade;	//has grenade?
		bool sheild;		//has sheild?
		bool speedBoost;	//has speedboost?
		float speedBoostTime; //time speedbost activated
		float sheildTime;	//time sheild activated
		float previousTime;	//previous time 

		float xPos;			// x position
		float yPos;			// y position
		float xSpeed;		// x speed
		float ySpeed;		// y speed

		float tankHeight;	//tanks height
		float tankWidth;	//tanks width

		float rotation;		// tank rotation
		float leftSpeed;// left rotation speed
		float rightSpeed; // rigght rotation speed

		float turretRotation; //turret rotation
		bool canFire;		//can tank fire (disables firing so tank can be reloaded, etc.)
		bool reload;		//tank reload (enables canFire)

		std::vector<bulletInfo> bulletArray;

		//testing
		int testInt;
		float testFloat;
		bool testbool;
};
#endif /* PLAYER_H_ */