#include "Styles.h"


sVelocity::sVelocity(double x, double y, double z, bool exit)
:sBasic(exit)
{
	xDelta = x;
	yDelta = y;
	zDelta = z;
}
void sVelocity::setPlayerEnemy(bool isEnemy)
{
	if(type < 100)
	{
		if(isEnemy)
		{
			type += ENEMY;
		}
		else
		{
			type += PLAYER;
		}
	}
}
sBasic* sVelocity::makeBasic()
{
	return reinterpret_cast<sBasic*>(this);
}

sShip::sShip(int a, Registry* r, Sprite* b, double bx, double by, double bz, double fd, double x, double y, double z)
:sVelocity(x, y, z)
{
	type += SHIP;
	reg = r;
	armor = a;
	bulletX = bx;
	bulletY = by;
	bulletZ = bz;
	bullet = b;
	fireCurr = 0;
	fireDelta = fd;
}
sBasic* sShip::makeBasic()
{
	return reinterpret_cast<sBasic*>(this);
}


sBullet::sBullet(int p, double x, double y, double z)
:sVelocity(x,y,z)
{
	
	type += BULLET;
	power = p;
}

sBasic* sBullet::makeBasic()
{
	return reinterpret_cast<sBasic*>(this);
}

sPowerUp::sPowerUp(int p, double x, double y, double z)
:sVelocity(x,y,z)
{
	type += POWERUP;
	powerup = p;
}

sBasic* sPowerUp::makeBasic()
{
	return reinterpret_cast<sBasic*>(this);
}

int basicUpdate(double delta, sBasic* args, SpriteController* partner)
{
	sVelocity* s = reinterpret_cast<sVelocity*>(args);

	if(s->isExiting)
	{
		return DESTROY;
	}

	//update xdelta, ydelta, zDelta, FrameDelta
	partner->xCurr = partner->xCurr + s->xDelta * delta;
	partner->yCurr = partner->yCurr + s->yDelta * delta;
	partner->zCurr = partner->zCurr + s->zDelta * delta;
	return NORMAL;
}

int enemyUpdate(double delta, sBasic* args, SpriteController* partner)
{
	sShip* tmp = reinterpret_cast<sShip*>(args);
	if(tmp->isExiting)
	{
		if(partner->getCurrentState() != 3)
		{
			partner->setCurrentState(3);
			partner->setCurrentFrame(0);
			partner->setFrameDelta(8);
		}
		if(partner->getCurrentFrame() + 1 == partner->getMaxFrames())
		{
			return DESTROY;
		}
		return NORMAL;
	}
	tmp->fireCurr = tmp->fireCurr+ tmp->fireDelta*delta;
	if(tmp->fireCurr > 1 && !tmp->isExiting)
	{
		tmp->fireCurr = tmp->fireCurr-1;
		//make bullet here
		sBullet* bVals = new sBullet;
		bVals->power = 10;
		bVals->xDelta = tmp->bulletX;
		bVals->yDelta = tmp->bulletY;
		bVals->zDelta = tmp->bulletZ;

		SpriteController* b = new SpriteController(tmp->bullet, bVals->makeBasic(), basicUpdate, 0, 0, partner->xCurr, partner->yCurr + 20, 1);
		b->setCurrentState(1);
		tmp->reg->add(b, true, ENEMYLIST);
	}
	if(tmp->isExiting)
	{
		tmp->xDelta = tmp->xDelta * 0.95;
		tmp->yDelta = tmp->yDelta * 0.95;
	}
	partner->xCurr = partner->xCurr + tmp->xDelta * delta;
	partner->yCurr = partner->yCurr + tmp->yDelta * delta;
	partner->zCurr = partner->zCurr + tmp->zDelta * delta;
	return NORMAL;
}

int backgroundStyleUpdate(double delta, sBasic* args, SpriteController* partner)
{
	basicUpdate(delta, args, partner);

	if(partner->xCurr<-640)
	{
		partner->xCurr+=1280;
	}
	return NORMAL;
}
SpriteController* makeEnemy(int x, int y, Loader* gameLoader, Registry* r)
{
	sShip* temp = new sShip(10, r, gameLoader->sprites.lookup("Bullet"), -240, 0, 0, 1, -100, 0, 0);
	return new SpriteController(gameLoader->sprites.lookup("Roller"), temp->makeBasic(), enemyUpdate, 0, 0, x, y); 
}

SpriteController* makePowerup(int x, int y, Loader* ld)
{
	sPowerUp* temp = new sPowerUp(1, -100, 0, 0);
	return new SpriteController(ld->sprites.lookup("PowerUp1"), temp->makeBasic(), basicUpdate, 0, 0, x, y);
}
SpriteController* makeBullet(int x, int y, Loader* gameLoader, Registry* r)
{
	sBullet* bVals = new sBullet;
	bVals->power = 10;
	bVals->xDelta = 0;
	bVals->yDelta = 0;
	bVals->zDelta = 0;

	return new SpriteController(gameLoader->sprites.lookup("Bullet"), bVals->makeBasic(), basicUpdate, 0, 0, x, y, 1);
}





slaveStyle::slaveStyle()
{
	sBasic();
	master = 0;
	xOffset = 0;
	yOffset = 0;
}
sBasic* slaveStyle::makeBasic()
{
	return reinterpret_cast<sBasic*>(this);
}


int slaveUpdate(double delta, sBasic* args, SpriteController* partner)
{
	slaveStyle* temp = reinterpret_cast<slaveStyle*>(args);
	

	if(temp->isExiting)
	{
		return DESTROY;
	}
	

	temp->xDelta = (temp->master->xCurr - (partner->xCurr-temp->xOffset))*3/4;
	temp->yDelta = (temp->master->yCurr - (partner->yCurr+temp->yOffset))*3/4;
	partner->xCurr = partner->xCurr + temp->xDelta * delta;
	partner->yCurr = partner->yCurr + temp->yDelta * delta;
	/*if(temp->master->xCurr != partner->xCurr - temp->xOffset)
	{
		int xGoal = temp->master->xCurr;
		int xCurrent = partner->xCurr - temp->xOffset;
		if(xGoal > xCurrent)
		{
			temp->xDelta = SLAVESPEED;
		}
		else if(xGoal < xCurrent)
		{
			temp->xDelta = SLAVESPEED * -1;
		}
		else
		{
			temp->xDelta = 0;
		}
		partner->xCurr = partner->xCurr + temp->xDelta * delta;
		
	}
	if(temp->master->yCurr != partner->yCurr - temp->yOffset)
	{
		int yGoal = temp->master->yCurr;
		int yCurrent = partner->yCurr+temp->yOffset;
		if(yGoal > yCurrent)
		{
			temp->yDelta = SLAVESPEED;
		}
		else if(yGoal < yCurrent)
		{
			temp->yDelta = SLAVESPEED * -1;
		}
		else
		{
			temp->yDelta = 0;
		}
		partner->yCurr = partner->yCurr + temp->yDelta * delta;
	}*/

	
	
	
	//partner->zCurr = partner->zCurr + temp->zDelta * delta;
	return NORMAL;
}