#include "spritecontroller.h"
#include <iostream>

//////////
//Builds sBasic object.  Not sure why you'd want an autoexiting sprite but the option is there.
//
//////////
sBasic::sBasic(bool exit)
{
	type = 0;
	isExiting = exit;
}


//////////
// Deletes the only pointers that are unique to this object: location and game variables.
//
//////////
SpriteController::~SpriteController()
{
	delete Location;
	delete gameVars;
}


//////////
// Basic full initialization of all variables at once with basic bounds checking.
//  This function is safe-ish.
//
//////////
bool SpriteController::init(Sprite* s, sBasic* gVars, int (*func)(double,sBasic*,SpriteController*),int tState,int tFrame,int x,int y,int z)
{
	isVisible = true;
	frameDelta = 0;
	frameCurr = 0;
	stateCurr = 0;
	sprite = s;
	if(s!= 0)
	{
		setCurrentFrame(tFrame);
		setCurrentState(tState);
	}
	xCurr = double(x);
	yCurr = double(y);
	zCurr = double(z);
	frameCurr=double(tFrame);
	Location = new SDL_Rect;
	Location->x = int(xCurr);
	Location->y = int(yCurr);
	Location->w = 0;
	Location->h = 0;
	gameVars = gVars;
	gameFunc = func;
	return true;
}


//////////
// If the object is visible, instruct the sprite to draw itself to the screen.
//
//////////
void SpriteController::draw(SDL_Surface* screen)
{
	if(isVisible)
		sprite->draw(screen,Location,stateCurr,(int)frameCurr);
}



bool SpriteController::isPixelTransparent(int x, int y)
{
	return sprite->isPixelTransparent(stateCurr, (int)frameCurr, x - Location->x, y - Location->y);
}


//////////
// Updates the location and game variables of the sprite for the time given.
//  This function returns the status of the object (NORMAL or DESTROY).
//		NORMAL - this object is ready to continue with it's next pass through the loop
//		DESTROY - this object is ready to exit the program
//////////
int SpriteController::update(double timeChunk)
{
	// This value allows the object to return status information to the window object that is updating it.
	int returnValue = NORMAL;

	// If there is a game function for this object, run it
	if(gameFunc != 0)
	{
		returnValue = gameFunc(timeChunk, gameVars, this);
	}


	// Update the current location of the sprite on screen
	Location->x = int(xCurr);
	Location->y = int(yCurr);
	

	// Advance the animation of the sprite.
	frameCurr = frameCurr + frameDelta*timeChunk;

	// If the current frame exceeds the number of frames, loop the animation
	if(sprite->getFrames(stateCurr) <= frameCurr)
	{
		frameCurr=0.0f;
	}

	return returnValue;
}


//////////
// These are safe mutator functions.  These do nothing if the input is out of bounds.
//
//////////
void SpriteController::setCurrentState(int i)
{
	if(i >= sprite->getNumberOfStates() || i < 0)
	{
		return;
	}
	stateCurr = i;
	setCurrentFrame(0);	
}

void SpriteController::setCurrentFrame(double i)
{
	if(i > sprite->getFrames(stateCurr) || i < 0)
	{
		return;
	}
	frameCurr = i;
}
/* Redundant function
void SpriteController::setFrameCurr(double i)
{
	if(i > sprite->getFrames(stateCurr) || i < 0)
	{
		return;
	}
	frameCurr = i;
}*/

void SpriteController::setFrameDelta(double d)
{
	if( d < 0)
	{
		return;
	}
	frameDelta = d;
}

void SpriteController::setStyle(sBasic* newVars, int (*func)(double,sBasic*,SpriteController*))
{
	// This function may never be used since these can be set in the constructor.
	if(gameVars != 0)
	{
		delete gameVars;
	}
	gameVars = newVars;		
	gameFunc = func;
}



