#include "GameInfo.h"
#include "ShapeArray.h"
float distanceMath(float a, float b, float x, float y);
void draw(HDC deviceContext, gameInfo* currentGame)   
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// clear the screen and the depth buffer

	glEnableClientState(GL_VERTEX_ARRAY);						// we need enable vertices to draw polygons (obviously)
	glEnableClientState(GL_COLOR_ARRAY);						// we want to use colors too
	
	glMatrixMode(GL_MODELVIEW);									// we are going to affect how models are drawn
    
	
	// player loop
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		
		glLoadIdentity();											// start with the identity matrix (i.e. no transformation)
			glPushMatrix();


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										TANK
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		

				glVertexPointer(3, GL_FLOAT, 0, myTankArray); //load tank array
				if (i == 0)
				{
				glColorPointer(4, GL_FLOAT, 0, myTankColorArray1); //load tank colour array
				}
				else
				{
				glColorPointer(4, GL_FLOAT, 0, myTankColorArray2); //load tank colour array
				}
					glPushMatrix();	// save the current matrix state (no translations/rotations)

						glTranslatef(currentGame->playerArray[i]->xPos, currentGame->playerArray[i]->yPos,-10.0f);	// move the tank on x/y and back on z
						glRotatef(currentGame->playerArray[i]->rotation, 0.0, 0.0, 1.0); //rotate the tank on z
						glDrawArrays(GL_TRIANGLES, 0, 6);	//draw triangles for the tank (2 triangles)

							glPushMatrix(); // save the current matrix state (tank translations/rotations)

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										TURRET
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			

					
				glVertexPointer(3, GL_FLOAT, 0, myTurretArray);	//load the turret array
					if (i == 0)
					{
						glColorPointer(4, GL_FLOAT, 0, myTurretColorArray1); //load the turret colour array		
					}
					else
					{
					glColorPointer(4, GL_FLOAT, 0, myTurretColorArray2); //load the turret colour array		
					}

					glRotatef(currentGame->playerArray[i]->turretRotation, 0.0f, 0.0f, 1.0f); //Turret rotation on z (moves with the tank)
								glDrawArrays(GL_TRIANGLES, 0, 12);	//draw triangles for the Turret (4 triangles - 2 for turret body and 2 for turret)
							glPopMatrix();	//clear the matrix (turret translations/rotations)
					glPopMatrix();//clear the matrix (turret translations/rotations)
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										BULLET
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

				glVertexPointer(3, GL_FLOAT, 0, myBulletArray);	 //load bullet array
				glColorPointer(4, GL_FLOAT, 0, myBulletColorArray);	//load bullet colour array

				for(unsigned j = 0; j < currentGame->playerArray[i]->bulletArray.size(); j++) // for loop so the following translations/rotations apply to all bullets
				{
					glPushMatrix(); //save the matrix so we can edit the bullet

						glTranslatef(currentGame->playerArray[i]->bulletArray[j].xPos, currentGame->playerArray[i]->bulletArray[j].yPos,-10.0f); //moves the bullet on x/y and moves the bullet back on z
						glRotatef(currentGame->playerArray[i]->bulletArray[j].bulletRotation, 0.0f, 0.0f, 1.0f); //rotates the bullet
						glDrawArrays(GL_TRIANGLES, 0, 6);	//draw triangles for the bullets (2 triangles)
					glPopMatrix(); //clear the last matrix as we no longer need the bullet info
				}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										PICKUPS
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		

				for (unsigned s = 0; s < MAX_NUMBER_OF_PICKUPS; s++)
				{
					glPushMatrix();
					if (currentGame->powerUpArray[s].visible)
					{
						glVertexPointer(3, GL_FLOAT, 0, sheildPickupArray);	 //load PICKUPS array
						if (currentGame->powerUpArray[s].powerUpType == 0) //colour of pickup is dependant on type, this is worked out here.
						{
							glColorPointer(4, GL_FLOAT, 0, sheildPickupColourArray); //load the sheild colour array
						}
						if (currentGame->powerUpArray[s].powerUpType == 1)
						{
							glColorPointer(4, GL_FLOAT, 0, specialPickupColourArray); //load the specialshot colour array
						}
						if (currentGame->powerUpArray[s].powerUpType == 2)
						{
							glColorPointer(4, GL_FLOAT, 0, grenadePickupColourArray); //load the grenade colour array	
						}
						if (currentGame->powerUpArray[s].powerUpType == 3)
						{
							glColorPointer(4, GL_FLOAT, 0, speedPickupColourArray); //load the speed colour array	
						}
						glTranslatef(currentGame->powerUpArray[i].xPos, currentGame->powerUpArray[i].yPos,-10.0f);
						glDrawArrays(GL_TRIANGLES, 0, 12);	//draw triangles for the bullets (2 triangles)
						glPopMatrix();	
					}
			
				}
			glPopMatrix();		
	}
				
	glDisableClientState(GL_VERTEX_ARRAY);						// turn off vertex rendering again, just in case
	glDisableClientState(GL_COLOR_ARRAY);						// turn off vertex colors again, just in case
    
	SwapBuffers(deviceContext);									// put our triangles on the screen!
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
	currentGame->playerArray[i]->tankHeight = distanceMath(myTankArray[0],myTankArray[1],myTankArray[6],myTankArray[7]);
	currentGame->playerArray[i]->tankWidth = distanceMath(myTankArray[0],myTankArray[1],myTankArray[3],myTankArray[4]);
		for (unsigned j = 0; j < currentGame->playerArray[i]->bulletArray.size(); j++) //for loop to loop through all bullets and apply movement
				{	
				currentGame->playerArray[i]->bulletArray[j].bulletHeight= distanceMath(myBulletArray[0],myBulletArray[1],myBulletArray[6],myBulletArray[7]);
				currentGame->playerArray[i]->bulletArray[j].bulletWidth = distanceMath(myBulletArray[0],myBulletArray[1],myBulletArray[3],myBulletArray[4]);
				}
	}

}
