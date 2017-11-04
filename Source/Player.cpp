#include "GameInfo.h" 
float distanceMath(float a, float b, float x, float y);
// this sets up the default values that are common to all players
playerInfo::playerInfo()
{
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;

	turretLeft = false;
	turretRight = false;

	fireNormal = false;
	fireSpecial = false;
	fireGrenade = false;
	hasSpecial = SPECIAL_WEAPONS;
	hasGrenade = SPECIAL_WEAPONS;
	sheild = SHEILD_ON_OFF;
	speedBoost = SPEEDBOOST_ON_OFF;
	speedBoostTime = GetTickCount();
	sheildTime = 0.0f;
	previousTime = 0.0f;

	xPos = 0.0f;
	yPos = 0.0f;
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	tankHeight = 0.0f;
	tankWidth = 0.0f;

	rotation = 0.0f;
	leftSpeed = 0.0f;
	rightSpeed = 0.0f;

	turretRotation = 0.0f;
	canFire = true;
	reload = false;

	//testing
	testInt = 0;
	testFloat = 0.0f;
	testbool = false;

}