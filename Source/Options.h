#ifndef OPTIONS_H_
#define OPTIONS_H_

//powerup on start options
#define SPECIAL_WEAPONS true; //special weapons enabled at start of matches?
#define SPEEDBOOST_ON_OFF false; //speedboost enabled at start?
#define SHEILD_ON_OFF false; //sheild on at start?

//sets powerups on map
#define POWERUPTYPE 3//0 = sheild, 1 = special fire, 2 = grenade, 3 = speedboost
#define POWERUPS_ON_OFF false; // turns on or turns off powerups on the map ******this does not work correctly******

//controls
//PLAYER1
#define PLAYER1UP 0x57 //player 1 forward
#define PLAYER1DOWN 0x53 //player 1 backwards
#define PLAYER1LEFT 0x41 //player 1 turn left
#define PLAYER1RIGHT 0x44 //player 1 turn right
#define PLAYER1ROTATELEFT 0x51 //player 1s turret left
#define PLAYER1ROTATERIGHT 0x45 //player 1s turret right
#define PLAYER1SHOOT VK_SPACE //player 1 shoot
#define PLAYER1RELOAD 0x52 //player 1 reload
#define PLAYER1SPECIAL 0x31 //player 1 special shot
#define PLAYER1GRENADE 0x32 //player 1 grenade
#define PLAYER1SHEILD 0x42 //player 1 sheild

//PLAYER2
#define PLAYER2UP 0x68 //player 2 forward
#define PLAYER2DOWN 0x65 //player 2 backward
#define PLAYER2LEFT 0x64 //player 2 turn left
#define PLAYER2RIGHT 0x66 //player 2 turn right
#define PLAYER2ROTATELEFT  0x67 //player 2s turret left
#define PLAYER2ROTATERIGHT 0x69 //player 2s turret right
#define PLAYER2SHOOT 0x60 //player 2 shoot
#define PLAYER2RELOAD 0x61 //player 2 reload
#define PLAYER2SPECIAL 0x62 //player 2 special shot
#define PLAYER2GRENADE 0x63 //player 2 grenade
#define PLAYER2SHEILD 0x6E //player 2 sheild


#endif /* OPTIONS_H_ */