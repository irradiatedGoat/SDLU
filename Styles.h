#ifndef _STYLES_H_
#define _STYLES_H_
#include "SDLUtility.h"

#define PLAYERLIST LISTA
#define ENEMYLIST LISTB


#define BASE		0
#define SHIP		10
#define BULLET		20
#define POWERUP		50
// probably wont use these.
#define PLAYER		100
#define ENEMY		200

#define SLAVESPEED 100


// class that uses delta values to move the sprite around on the screen
class sVelocity : public sBasic
{
public:
	double  xDelta, yDelta, zDelta;
	sVelocity(double x = 0, double y = 0, double z = 0, bool exit = false);
	// may only be called once and permenantly sets the type to either a player or an enemy object
	void setPlayerEnemy(bool isEnemy);
	sBasic* makeBasic();
};


class sShip : public sVelocity
{
public:
	int armor;
	double bulletX, bulletY, bulletZ;
	double fireCurr, fireDelta;
	Registry* reg;
	Sprite* bullet;
	sShip(int a, Registry* r, Sprite* b = 0, double bx = 0, double by = 0, double bz = 0, double fd = 0, double x = 0, double y = 0, double z = 0);
	sBasic* makeBasic();
};

class sBullet : public sVelocity
{
public:
	int power;
	sBullet(int p = 0, double x = 0, double y = 0, double z = 0);
	sBasic* makeBasic();
};
int basicUpdate(double delta, sBasic* args, SpriteController* partner);
int enemyUpdate(double delta, sBasic* args, SpriteController* partner);
int backgroundStyleUpdate(double delta, sBasic* args, SpriteController* partner);

class sPowerUp : public sVelocity
{
public:
	int powerup;
	sPowerUp(int p = 1, double x = 0, double y = 0, double z = 0);
	sBasic* makeBasic();
};

SpriteController* makeEnemy(int x, int y, Loader* ld, Registry* r);
SpriteController* makePowerup(int x, int y, Loader* ld);
SpriteController* makeBullet(int x, int y, Loader* gameLoader, Registry* r);

//Testing code
class slaveStyle : public sVelocity
{
public:
	SpriteController* master;
	int xOffset, yOffset;
	slaveStyle();
	sBasic* makeBasic();

};

int slaveUpdate(double delta, sBasic* args, SpriteController* partner);


#endif