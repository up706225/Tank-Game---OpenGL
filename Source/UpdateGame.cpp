#include "GameInfo.h"
bool isCollision(float px, float py, float bx, float by, float bWidth,  float bHeight, float bAngle); //forward declaration for collision
float radianMath(float a); //forward declaration for radianMath function
float distanceMath(float a, float b, float x, float y); //forward declaration for distance math
// this is the main function in terms of gameplay
// we pass in a pointer to the current game instance,
// so we can read and write information about the players and the world.
void updateGame(HDC deviceContext, gameInfo* currentGame)	
{
// do game logic here

// work out how close to the ideal frame delta the last frame delta was...
float deltaAdjustment = (float)currentGame->frameDelta / IDEAL_DELTA;
// a result higher than 1 suggests the PC couldn't meet the ideal FPS, so the animation will be scaled up to compensate, and therefore could appear jerky.
// a result of 1 or less means the PC is comfortable at the frame rate and the animation will be scaled down so it doesn't run too fast.

// this bit updates the rotation of each player if they are holding their key down...
	for (int i = 0; i < NUM_PLAYERS; i++) //for loop that goes through all players and checks their key pushes and applies the movement
	{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										POWERUPS
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		float speedPowerUp = 0.0f;

	// ################################### TANK - SCREEN SWAP ######################################
		if (currentGame->playerArray[i]->xPos > WIDTHINCODE || currentGame->playerArray[i]->xPos < -WIDTHINCODE) //if player goes out of bounds on x
			{
					currentGame->playerArray[i]->xPos = (-currentGame->playerArray[i]->xPos); // move them to the oposite side

			}
		if (currentGame->playerArray[i]->yPos > HEIGHTINCODE || currentGame->playerArray[i]->yPos < -HEIGHTINCODE) //if player goes out of bounds on y
			{
					currentGame->playerArray[i]->yPos = (-currentGame->playerArray[i]->yPos); // move them to the oposite side

			}
	// ################################### SPEEDBOOST ######################################		
		if (currentGame->playerArray[i]->speedBoost)
		{
			speedPowerUp = SPEEDBOOST; //adds speedboost difference to variable, used when working out speed (is 0.0 by default so usually has no effect)
			if ((GetTickCount() - currentGame->playerArray[i]->speedBoostTime) > SPEEDBOOST_TIME) //if speeedboost has been active for more than so many seconds
			{
				currentGame->playerArray[i]->speedBoost = false; //remove it
				speedPowerUp = 0.0f; //and set value back to default so player slows again
			}
		}	
	// ################################### SHEILD ######################################
		if ((currentGame->playerArray[i]->sheild && GetTickCount() - currentGame->playerArray[i]->sheildTime) > SHEILDBOOST_TIME) //if sheild is active for more than so many seconds
		{
			currentGame->playerArray[i]->sheild = false; //turn off sheild
		}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//									TANK ROTATION
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	// ################################### RIGHT ROTATION ######################################
		if (currentGame->playerArray[i]->rightPressed || currentGame->playerArray[i]->rightSpeed > 0) //checks if left is pressed or if righ rotation speed is above 0 (this is needed for the rotation if statement below)
		{
			if (currentGame->playerArray[i]->rightPressed && currentGame->playerArray[i]->rightSpeed <= MAX_ROTATION_SPEED * deltaAdjustment) //checks that right is pressed and that the rotation speed doesnt exceed the max rotation speed
			{
				currentGame->playerArray[i]->rightSpeed += (ROTATION_SPEED * deltaAdjustment);	//rotation amount dependendant on frame rate, so we multiply the ideal ROTATION_SPEED by the delta adjustment.
			}
			if (currentGame->playerArray[i]->rotation < 360.0f) //Make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
			{
				currentGame->playerArray[i]->rotation += 360.0f; //sets rotation to 0
			}
		}  
	// ################################### LEFT ROTATION ######################################
		if (currentGame->playerArray[i]->leftPressed || currentGame->playerArray[i]->leftSpeed > 0) //checks if left is pressed or if left rotation speed is above 0 (this is needed for the rotation if statement below)
		{
			if (currentGame->playerArray[i]->leftPressed && currentGame->playerArray[i]->leftSpeed <= MAX_ROTATION_SPEED * deltaAdjustment)//checks that left is pressed and that the rotation speed doesnt exceed the max rotation speed
			{
				currentGame->playerArray[i]->leftSpeed += (ROTATION_SPEED * deltaAdjustment);
			}
			if (currentGame->playerArray[i]->rotation > 360.0f) //Make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
			{
				currentGame->playerArray[i]->rotation -= 360.0f; //sets rotation to 0
			}
		}  

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//									TURRET ROTATION
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// ################################### LEFT TURRET ROTATION ######################################
		if (currentGame->playerArray[i]->turretRight) 
		{
			currentGame->playerArray[i]->turretRotation -= (TURRET_SPEED * deltaAdjustment); //adds right rotation to the turret
			if (currentGame->playerArray[i]->turretRotation < 360.0f) //If statement to make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
			{
				currentGame->playerArray[i]->turretRotation += 360.0f; //sets turret rotation to 0
			}
		}  
	// ################################### LEFT TURRET ROTATION ######################################
		if (currentGame->playerArray[i]->turretLeft) 
		{
			currentGame->playerArray[i]->turretRotation += (TURRET_SPEED * deltaAdjustment); //adds left rotation to the turret
			if (currentGame->playerArray[i]->turretRotation > 360.0f) //If statement to make sure that rotation stays under 360 degrees (so when it gets to +360 degrees, it takes away by 360)
			{
				currentGame->playerArray[i]->turretRotation -= 360.0f; //sets turret rotation to 0
			}
		}  
	// ################################### RADIAN MATH ######################################
		float radian = radianMath(currentGame->playerArray[i]->rotation); // sends rotation to radianMath function to work out the radian
		float turretRadian = radianMath(currentGame->playerArray[i]->turretRotation);// sends turret rotation to radianMath function to work out the radian
	
		
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										MOVEMENT
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	// ################################### FORWARD ######################################	
		if (currentGame->playerArray[i]->upPressed) 
		{

			currentGame->playerArray[i]->xSpeed += ((MOVE_SPEED + speedPowerUp) * deltaAdjustment); //adds forward movement to xSpeed
			currentGame->playerArray[i]->ySpeed += ((MOVE_SPEED + speedPowerUp) * deltaAdjustment); //adds forward movement to ySpeed
		}
	// ################################### BACKWARDS ######################################
		if (currentGame->playerArray[i]->downPressed)
		{
			currentGame->playerArray[i]->xSpeed -= ((MOVE_SPEED + speedPowerUp) * deltaAdjustment); //adds forward movement to xSpeed
				
			currentGame->playerArray[i]->ySpeed -= ((MOVE_SPEED + speedPowerUp)* deltaAdjustment); //adds forward movement to ySpeed
		}
	// ################################### MAXSPEED CHECK ######################################
		if (currentGame->playerArray[i]->xSpeed <= MAX_SPEED * deltaAdjustment) //checks the xSpeed is under the max speed
		{
			currentGame->playerArray[i]->xSpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
		}
		if (currentGame->playerArray[i]->ySpeed <= MAX_SPEED * deltaAdjustment)  //checks the ySpeed is under the max speed
		{
			currentGame->playerArray[i]->ySpeed += (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed
		}
		if (currentGame->playerArray[i]->xSpeed >= MAX_REVERSE * deltaAdjustment) //checks the xSpeed is under the max reverse speed
		{
			currentGame->playerArray[i]->xSpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to xSpeed
		}
		if (currentGame->playerArray[i]->ySpeed >= MAX_REVERSE * deltaAdjustment) //checks the ySpeed is under the max reverse speed
		{
			currentGame->playerArray[i]->ySpeed -= (MOVE_SPEED * deltaAdjustment); //adds forward movement to ySpeed
		}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//						COLLISION/ACCELERATION AND DECELERATION/FRICTION
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			int t = 0;
			if (i == 0)
			{
				t = 1;
			}
	// ################################### COLLISION - ROTATION ######################################
			if (isCollision(currentGame->playerArray[i]->xPos, currentGame->playerArray[i]->yPos, currentGame->playerArray[t]->xPos, currentGame->playerArray[t]->yPos, currentGame->playerArray[i]->tankWidth,currentGame->playerArray[i]->tankHeight, radian)) //checks if tanks are coliding
			{
				currentGame->playerArray[i]->leftSpeed = -currentGame->playerArray[i]->leftSpeed; //if they are colliding, make leftSpeed negative leftSpeed (so player moves in oposite direction)
				currentGame->playerArray[i]->rightSpeed = -currentGame->playerArray[i]->rightSpeed; //if they are colliding, make rightSpeed negative rightSpeed (so player moves in oposite direction)
			}
			else
			{
	// ################################### FRICTION - ROTATION ######################################
			currentGame->playerArray[i]->leftSpeed -= currentGame->playerArray[i]->leftSpeed * (FRICTION * deltaAdjustment); //friction for left rotation (used in acceleration/deceleration)
			currentGame->playerArray[i]->rightSpeed -= currentGame->playerArray[i]->rightSpeed * (FRICTION * deltaAdjustment); //friction for right rotation (used in acceleration/deceleration)
			}
	// ################################### APPLIES ROTATION ######################################
			currentGame->playerArray[i]->rotation += currentGame->playerArray[i]->leftSpeed; //rotates the tank left
			currentGame->playerArray[i]->rotation -= currentGame->playerArray[i]->rightSpeed; //rotates the tank right
	// ################################### COLLISION - FORWARD/BACK ######################################			
			if (isCollision(currentGame->playerArray[t]->xPos, currentGame->playerArray[t]->yPos, currentGame->playerArray[i]->xPos, currentGame->playerArray[i]->yPos,currentGame->playerArray[i]->tankWidth,currentGame->playerArray[i]->tankHeight, radian)) //checks if tanks are coliding
			{
				currentGame->playerArray[i]->xSpeed = -currentGame->playerArray[i]->xSpeed; //if they are colliding, make xSpeed negative xSpeed (so player moves in oposite direction)
				currentGame->playerArray[i]->ySpeed = -currentGame->playerArray[i]->ySpeed; //if they are colliding, make ySpeed negative ySpeed (so player moves in oposite direction)
			}
			else // if not colliding, apply friction (needed so tanks do not pass through each other)
	// ################################### FRICTION  ######################################
			{
			currentGame->playerArray[i]->xSpeed -= currentGame->playerArray[i]->xSpeed * (FRICTION * deltaAdjustment); //applies friction to xSpeed (used in acceleration/deceleration)
			currentGame->playerArray[i]->ySpeed -= currentGame->playerArray[i]->ySpeed * (FRICTION * deltaAdjustment); //applies friction to ySpeed (used in acceleration/deceleration)
			}
	// ################################### APPLIES MOVEMENT ######################################
			currentGame->playerArray[i]->xPos += ((currentGame->playerArray[i]->xSpeed) * (float)cos(radian)); //movement on x - forward and reverse
			currentGame->playerArray[i]->yPos += ((currentGame->playerArray[i]->ySpeed) * (float)sin(radian)); //movement on y - forward and reverse
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										Bullets
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		if (currentGame->playerArray[i]->canFire) //checks if player can fire (dependant on reloading, etc.)
		{
	// ################################### NORMAL SHOT - VARIABLES ######################################
			if (currentGame->playerArray[i]->fireNormal || currentGame->playerArray[i]->fireSpecial || currentGame->playerArray[i]->fireGrenade)
			{
				float grenadeAngle = 0.0f; //values set here are used for working out normal bullets (special bullets edit these values, this saves having the bullets section written 3 times)
				float specialAngle = 0.0f;
				float shootDistance = 0.7f;
				int totalBullets = 1;
				float bulletLife = NORMAL_FIRE_LIFE;
	// ################################### SPECIAL SHOT - VARIABLES ######################################
				if (currentGame->playerArray[i]->fireSpecial) //values here are for special bullets
				{
					shootDistance = 1.0;
					totalBullets = 5;
					bulletLife = SPECIAL_FIRE_LIFE;
				}
	// ################################### GRENADE - VARIABLES ######################################
				if (currentGame->playerArray[i]->fireGrenade)//values here are for grenades 
				{
					shootDistance = 3.0;
					grenadeAngle = 30.0;
					totalBullets = 18;
					bulletLife = GRENADE_FIRE_LIFE;
				}
	// ################################### BULLET TOTAL ######################################
				for (int s = 0; s < totalBullets; s++) //runs through the total bullets required for the shot
				{
	// ################################### SPECIAL SHOT - CALCLUATIONS ######################################
					if (currentGame->playerArray[i]->fireSpecial) //if special, it gives the angle a specific value depending on what the value of s is in the loop
					{
						if (s == 1)
						{
							specialAngle = 10.0f;
						}
						if (s == 2)
						{
							specialAngle = -10.0f;
						}
						if (s == 3)
						{
							specialAngle = 20.0f;
						}
						if (s == 4)
						{
							specialAngle = -20.0f;
						}	
					}
	// ################################### GRENADE - VARIABLES ######################################
					if (currentGame->playerArray[i]->fireGrenade) //if grenade, it takes the angle set above and adds the value below each time the loop runs
					{
						grenadeAngle = grenadeAngle + 30.0f;
					}

	// ################################### BULLET CREATION ######################################
 					currentGame->playerArray[i]->canFire = false; //sets it so that player cannot fire
					bulletInfo tempBullet; // creates temp bullet info for transfering info about the bullet (using tanks info)
					tempBullet.xPos = currentGame->playerArray[i]->xPos + (shootDistance * (float)cos(turretRadian + radian)); //sets xpos for temp bullet
					tempBullet.yPos = currentGame->playerArray[i]->yPos + (shootDistance * (float)sin(turretRadian + radian)); //sets ypos for temp bullet
					tempBullet.xSpeed = (BULLET_SPEED * deltaAdjustment); //sets temp bullets speed using the speed defined in BULLET_SPEED#
					tempBullet.ySpeed = (BULLET_SPEED * deltaAdjustment); //sets temp bullets speed using the speed defined in BULLET_SPEED
					tempBullet.bulletRotation = (currentGame->playerArray[i]->turretRotation + currentGame->playerArray[i]->rotation + grenadeAngle + specialAngle);
					currentGame->playerArray[i]->previousTime = GetTickCount(); //sets previous time (for reload)
					tempBullet.startTime = GetTickCount(); //sets bullet start time
					tempBullet.bulletLife = bulletLife; // sets bullet life depending on type of bullet
					currentGame->playerArray[i]->bulletArray.push_back(tempBullet); //adds the temp bullet info to the bulletArray
				}
			}
		}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//								Bullets - movement/collision
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for (unsigned j = 0; j < currentGame->playerArray[i]->bulletArray.size(); j++) //for loop to loop through all bullets and apply movement
		{
			float bulletRadian = radianMath(currentGame->playerArray[i]->bulletArray[j].bulletRotation);
			int t = 0; 
			if (i == 0)// This is used ahead as the bullet needs to check each player, this simply checks what player and sets appropriately
			{
			t = 1;
			}
			// ################################### BULLET COLLISION ######################################
			if (isCollision(currentGame->playerArray[i]->bulletArray[j].xPos, currentGame->playerArray[i]->bulletArray[j].yPos, currentGame->playerArray[i]->xPos, currentGame->playerArray[i]->yPos,currentGame->playerArray[i]->tankWidth/2, currentGame->playerArray[i]->tankHeight/2, bulletRadian)||isCollision(currentGame->playerArray[i]->bulletArray[j].xPos, currentGame->playerArray[i]->bulletArray[j].yPos,currentGame->playerArray[t]->xPos, currentGame->playerArray[t]->yPos,currentGame->playerArray[i]->tankWidth/2, currentGame->playerArray[i]->tankHeight/2,bulletRadian))
			{
				currentGame->playerArray[i]->bulletArray.erase (currentGame->playerArray[i]->bulletArray.begin()+j); //deletes bullets after collision
				
				if (currentGame->playerArray[t]->sheild) //if the player has a sheild
				{
					currentGame->playerArray[t]->sheild = false; //remove it
				}
				else
				{
	// ################################### COLLISION - RESET GAME ######################################
				currentGame->playerArray[0]->xPos = PLAYER1XPOS; //moves player 1 to default x
				currentGame->playerArray[0]->yPos = PLAYER1YPOS; //moves player 1 to default y
				currentGame->playerArray[1]->xPos = PLAYER2XPOS; //moves player 2 to default x
				currentGame->playerArray[1]->yPos = PLAYER2YPOS; //moves player 2 to default y
				currentGame->playerArray[0]->rotation = PLAYER1ROTATION; //sets player 1 rotateion to default
				currentGame->playerArray[1]->rotation = PLAYER2ROTATION; //sets player 2 rotateion to default
				currentGame->playerArray[0]->turretRotation = PLAYERTURRETROTATION; //sets player 1 turret rotateion to default
				currentGame->playerArray[1]->turretRotation = PLAYERTURRETROTATION; //sets player 2 turret rotateion to default
				currentGame->playerArray[0]->canFire = true; //sets players 1 ability to fire to true
				currentGame->playerArray[1]->canFire = true; //sets players 2 ability to fire to true
				currentGame->playerArray[0]->bulletArray.clear(); //deletes all bullets for player 1
				currentGame->playerArray[1]->bulletArray.clear(); //deletes all bullets for player 2
				currentGame->playerArray[0]->hasSpecial = SPECIAL_WEAPONS; //sets player 1s ability to use special shot to default
				currentGame->playerArray[0]->hasGrenade = SPECIAL_WEAPONS; //sets player 1s ability to use grenade to default
				currentGame->playerArray[0]->sheild = SHEILD_ON_OFF; //sets player 1s sheild to default
				currentGame->playerArray[0]->speedBoost = SPEEDBOOST_ON_OFF; //sets player 1s speedboost to default
				currentGame->playerArray[1]->hasSpecial = SPECIAL_WEAPONS; //sets player 2s ability to use special shot to default
				currentGame->playerArray[1]->hasGrenade = SPECIAL_WEAPONS; //sets player 2s ability to use grenade to default
				currentGame->playerArray[1]->sheild = SHEILD_ON_OFF; //sets player 2s sheild to default
				currentGame->playerArray[1]->speedBoost = SPEEDBOOST_ON_OFF; //sets player 1s speedboost to default
				}
			}	
			else
			{
	// ################################### BULLET SPEED - MAX ###################################### 
	//bullets used to go over their max speed occasionally, this fixes that
				if (currentGame->playerArray[i]->bulletArray[j].xSpeed > BULLET_SPEED * deltaAdjustment) //if bullet is over bullets speed on x
				{
					currentGame->playerArray[i]->bulletArray[j].xSpeed = BULLET_SPEED * deltaAdjustment; //set to speed on x
				}
				if (currentGame->playerArray[i]->bulletArray[j].ySpeed > BULLET_SPEED * deltaAdjustment) //if bullet is over bullets speed on y
				{
					currentGame->playerArray[i]->bulletArray[j].ySpeed = BULLET_SPEED * deltaAdjustment; //set to speed on t
				}
	
	// ################################### BULLET - SCREEN SWAP ######################################	
				if (currentGame->playerArray[i]->bulletArray[j].xPos > WIDTHINCODE || currentGame->playerArray[i]->bulletArray[j].xPos < -WIDTHINCODE) //if bullet goes offscreen on x
				{
					currentGame->playerArray[i]->bulletArray[j].xPos = (-currentGame->playerArray[i]->bulletArray[j].xPos); //swap bullet position on x

				}
				if (currentGame->playerArray[i]->bulletArray[j].yPos > HEIGHTINCODE || currentGame->playerArray[i]->bulletArray[j].yPos < -HEIGHTINCODE) //if bullet goes offscreen on y
				{
					currentGame->playerArray[i]->bulletArray[j].yPos = (-currentGame->playerArray[i]->bulletArray[j].yPos);//swap bullet position on x
				}
	// ################################### BULLET - STOP BUG ######################################	
	// bullets stops after firing, this resets its speed to make sure it moves 
				if (currentGame->playerArray[i]->bulletArray[j].xSpeed == 0.0f && currentGame->playerArray[i]->bulletArray[j].ySpeed == 0.0f) //THIS IS USED IF THE BULLET STOPS FOR ANY REASON
				{
					currentGame->playerArray[i]->bulletArray[j].xSpeed = BULLET_SPEED * deltaAdjustment; //set to speed on x
					currentGame->playerArray[i]->bulletArray[j].ySpeed = BULLET_SPEED * deltaAdjustment; //set to speed on x
				}
	// ################################### BULLET - DELETE AFTER TIME ######################################	
				if ((GetTickCount() - currentGame->playerArray[i]->bulletArray[j].startTime) > currentGame->playerArray[i]->bulletArray[j].bulletLife)//if bullet is alive longer than its total time
				{
					currentGame->playerArray[i]->bulletArray.erase (currentGame->playerArray[i]->bulletArray.begin()+j);//eratse bullet after time
					break;
				}
				// ################################### BULLET MOVEMENT ######################################
				//done last incase bullet is deleted before this
				currentGame->playerArray[i]->bulletArray[j].xPos += (((currentGame->playerArray[i]->bulletArray[j].xSpeed) * deltaAdjustment) * (float)cos(bulletRadian)); //uses the xPos set above to fire the bullet along the correct axis
				currentGame->playerArray[i]->bulletArray[j].yPos += (((currentGame->playerArray[i]->bulletArray[j].ySpeed) * deltaAdjustment) * (float)sin(bulletRadian)); //uses the yPos set above to fire the bullet along the correct axis
			}
		}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										Pickups
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		int pickUpWidth = WIDTHINCODE - 1.0f; //USED TO MAKE SURE PICKUPS DONT APPEAR OFFSCREEN - (NOT CURRENTLY USED)
		int pickUpHeight = HEIGHTINCODE - 1.0f; //USED TO MAKE SURE PICKUPS DONT APPEAR OFFSCREEN - (NOT CURRENTLY USED)
		int randomX = rand()%pickUpWidth-pickUpWidth; //USED TO MAKE GIVE BULLETS RANDOM X - (NOT CURRENTLY USED)
		int randomY = rand()%pickUpHeight-pickUpHeight; //USED TO MAKE GIVE BULLETS RANDOM Y - (NOT CURRENTLY USED)
		int randomPowerUp = rand()%3;	//RANDOMLY CHOOSE POWERUP - (NOT CURRENTLY USED)
		
	// ################################### PICKUPS - CREATES VALUES FOR ARRAY ######################################
		for (int t = 0; t < MAX_NUMBER_OF_PICKUPS; t++)
		{
			powerUpInfo tempPowerUp; //creates temppowerup
			tempPowerUp.visible = POWERUPS_ON_OFF; //makes it visible
			tempPowerUp.powerUpType = POWERUPTYPE; //assigns the type
			tempPowerUp.xPos = 0.0; //x position
			tempPowerUp.yPos = tempPowerUp.yPos + tempPowerUp.xPos; //y position
			currentGame->powerUpArray.push_back(tempPowerUp); //puts the temppowerup into array
		}

	// ################################### PICKUPS - ASSIGNS POWERS TO PICKUPS ######################################
			for (unsigned t = 0; t < currentGame->powerUpArray.size(); t++) //FOR EVERY PICKUP GENERATED
			{
				
				if (currentGame->powerUpArray[t].visible ) // IF THE PICKUP IS VISIBLE
				{
	// ################################### PICKUPS - COLLISION ######################################
					if (isCollision(currentGame->powerUpArray[t].xPos, currentGame->powerUpArray[t].yPos,currentGame->playerArray[i]->xPos, currentGame->playerArray[i]->yPos,1, 1, 0.0)) //IF PLAYER COLLIDES WITH PICKUP
					{
	// ################################### PICKUPS - SHEILD ######################################
						if (currentGame->powerUpArray[t].powerUpType == 0) 
						{
							currentGame->playerArray[i]->sheild = true; //Give player sheild
							currentGame->playerArray[i]->sheildTime = GetTickCount(); //start timer
						}
	// ################################### PICKUPS - SPECIAL SHOT ######################################
						if (currentGame->powerUpArray[t].powerUpType == 1)
						{
							currentGame->playerArray[i]->hasSpecial = true; //Give player special
						}
	// ################################### PICKUPS - GRENADE ######################################
						if (currentGame->powerUpArray[t].powerUpType == 2)
						{
							currentGame->playerArray[i]->hasGrenade = true; //Give player grenade
						}
	// ################################### PICKUPS - SPEEDBOOST ######################################
						if (currentGame->powerUpArray[t].powerUpType == 3)
						{
							currentGame->playerArray[i]->speedBoost = true; //Give player speedboost
							currentGame->playerArray[i]->speedBoostTime = GetTickCount(); //start timer
						}
						currentGame->powerUpArray[t].visible = false; // SET PICKUP TO VISIBLE IF COLLIDE (THIS SHOULD ALSO STOP THEM DRAWING)
					}
				//		currentGame->powerUpArray.erase (currentGame->powerUpArray.begin()+t);
				}
			}
					
		}
	
}

