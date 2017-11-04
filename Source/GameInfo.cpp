#include "GameInfo.h" 
// this sets up the default values that are common to all game instances
gameInfo::gameInfo()
{
	// create an array of pointers to players...
	playerArray = new playerInfo* [NUM_PLAYERS];

	// for each player in the array, allocate memory for that player
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		playerArray[i] = new playerInfo;
	}
	//set players default position
		playerArray[0]->xPos = PLAYER1XPOS; //moves player 1 left
		playerArray[0]->yPos = PLAYER1YPOS; //moves player 1 up
		playerArray[1]->xPos = PLAYER2XPOS; //moves player 2 right
		playerArray[1]->yPos = PLAYER2YPOS; //moves player 2 down
		playerArray[0]->rotation = PLAYER1ROTATION; //rotate player 1 
		playerArray[1]->rotation = PLAYER2ROTATION; //rotate player 2 
		playerArray[0]->turretRotation = PLAYERTURRETROTATION; //rotate player 1s turret 
		playerArray[1]->turretRotation = PLAYERTURRETROTATION; //rotate player 2s turret 

	// since the updateGame function requires a delta time from the previous frame for its calculations, 
	// this will not work on the first frame of the game as there will be no delta recorded for it to work with.
	// so we will pretend a value was obtained, and that it was "ideal"...
	frameDelta = IDEAL_DELTA;

	// initialise the other frame delta variables...
	frameStartTime = 0;
	frameEndTime = 0;


}

gameInfo::~gameInfo()
{
	// this is called when the game state is deleted (on quitting)
	
	// for each player in our player array, free up its memory and set its pointer to NULL
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		delete playerArray[i];
		playerArray[i] = NULL;
	}
	
	// then delete the array itself and set its pointer to NULL
	delete[] playerArray;
	playerArray = NULL;
	
}

