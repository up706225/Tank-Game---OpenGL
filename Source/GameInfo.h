#ifndef GAMEINFO_H_
#define GAMEINFO_H_

#include <windows.h>	// need to be able to create windows etc
#include <gl/gl.h>		// opengl header file
#include <gl/glu.h>		// glu header file - glu helps us set up the perspective projection
#include <cmath>		//math module
#include <iostream>
#include <ctime>		//time module
#include <stdlib.h>

using namespace std;

// some basic numbers to hold the position and size of the window
#define WIDTH		1200
#define HEIGHT		720
#define TOPLEFTX	50
#define TOPLEFTY	50
#define WIDTHINCODE 7.45f //used for swapping screen code on x
#define HEIGHTINCODE 4.7f //used for swapping screen code on y


// some player constants
#define ROTATION_SPEED	0.5f //tank rotation speed
#define MAX_ROTATION_SPEED	2.0f //max rotation speed
#define TURRET_SPEED	3.0f //turret rotation speed
#define MOVE_SPEED 0.02f //tank move speed
#define MAX_SPEED 0.1f //tank max speed
#define MAX_REVERSE -MAX_SPEED //tank max reverse speed
#define FRICTION 0.2f //friction in the world
#define BULLET_SPEED 0.3f //bullets move speed
#define NUM_PLAYERS		2 //max number of players
#define NUMBER_OF_PICKUPS 4 //number of total pickups
#define MAX_NUMBER_OF_PICKUPS 1 //max number to load at once
#define SPEEDBOOST 0.02f //speedboost value
#define SPEEDBOOST_TIME 2500.0f //speedboost time
#define SHEILDBOOST_TIME 2500.0f //sheild time

#define NORMAL_FIRE_LIFE 6000.0f //normal shot life
#define SPECIAL_FIRE_LIFE 1500.0f //special shot life
#define GRENADE_FIRE_LIFE 2500.0f //grenade life
#define RELOAD_TIME 250.0f //time to reload new bullet
// player position 
#define PLAYER1XPOS -5.0f; //default x for player1
#define PLAYER1YPOS 3.0f; //default y for player1
#define PLAYER2XPOS 5.0f; //default x for player 2
#define PLAYER2YPOS -3.0f; //default y for player 2
#define PLAYER1ROTATION 0.0f; //default rotation for player 1
#define PLAYER2ROTATION 180.0f; //default rotation for player 2
#define PLAYERTURRETROTATION 0.0f; //default rotation of turret for both players

#include "Options.h"

// some constants to help normalise the frame rate between different machines:

// IDEAL_FPS is a frame rate we can REASONABLY require from the user's PC, but is also high enough to provide smooth animation.
#define IDEAL_FPS		30

// IDEAL_DELTA is how long each frame would take in milliseconds if the game was running at the ideal frame rate.
#define IDEAL_DELTA		(1000 / IDEAL_FPS)

// later in the code, all animation updates will be normalised so the game will appear to run at the IDEAL_FPS, regardless of actual frame rate.
// this is why the IDEAL_FPS needs to be decent enough for smooth animation.
// *BUT* the downside to this is that if the PC cannot achieve a frame rate of IDEAL_FPS, the animation may appear jerky,
// because it will be updated by larger amounts in order to appear to be running at correct speed. 
// this is why the IDEAL_FPS also has to be easily-achievable by the user's pc, to minimise the chance of jerkiness.
#include "Player.h"	
#include "Pickups.h"
// this class holds all of the information about a game state
class gameInfo
{
	public:
		gameInfo();			// the constructor
		~gameInfo();		// the destructor

		
		// variables required for the frame delta (DWORD is basically a long integer)
		DWORD frameStartTime;	// what the system time (in millisecs) was at the start of the last frame
		DWORD frameEndTime;		// what the system time (in millisecs) was at the end of the last frame 
		DWORD frameDelta;		// difference between the two (in millisecs), i.e. how long the last frame took

		
		// the data for each player will be stored using an instance of the playerInfo class
		// but we will use dynamically-allocated memory, so it needs to be initialised using a pointer
		// we will use an array to hold the pointers to the players, in case we want to have 1000 players or something.
		// however, the array itself will also be dynamically allocated, so that needs to use a pointer too!
		// hence two stars rather than just one
		playerInfo** playerArray;
		std::vector<powerUpInfo> powerUpArray;
};

#endif /* GAMEINFO_H_ */