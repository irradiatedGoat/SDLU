#ifndef _SPRITECONTROLLER_H_
#define _SPRITECONTROLLER_H_
#include "sprite.h"

//////////////////////////////////////
//Spritecontroller.h
//
//  SpriteControllers handle everything needed to control and draw
//  every sprite onto the screen.  Sprites are contained in a pool.
//  Each sprite controller refrences a sprite from the pool, with many 
//  sprite controllers refrenceing the same sprite simultaneously.
//  The sprite controller keeps track of the location, state, and frame
//  and speed of animation. 
//  In addition the sprite controller keeps track of variables needed
//  by the game itself in the form of classes derived from sBasic.  This
//  game data is updated using the function refrenced by the gameFunc 
//  function pointer.
//
//////////////////////////////////////

#define NORMAL	100
#define DESTROY	200

// Game data place holder class.  This class must be derived from to do anything useful
class sBasic
{
protected:
	int type;	// Numeric classifier to be able to use reinterpret_cast from an sBasic pointer
				//   to a derived class pointer

public:
	bool isExiting;					// Flags this SpriteController as garbage if true


	sBasic(bool exit = false);		// Basic constructor 
	~sBasic(){};					// No pointers.  Nothing to destroy (before derivation.)


	int getType(){return type;};	// Basic access function
};


//  Class that ties everything together.
class SpriteController		
{
private:
	double	frameCurr,				// Current frame to display when draw is called (converted to int then)
			frameDelta;				// Rate at which frames of animation advance
	int stateCurr;					// Current state that the object is in.
	SDL_Rect* Location;				// X and Y coords on screen to draw (can be directly used by the SDL draw function with no conversion)
	Sprite* sprite;					// The sprite that this object uses to draw itself on screen.

	sBasic* gameVars;				// Functionally these do nothing for the engine but the enable 
									// the control of sprite objects by game code.
	int (*gameFunc)(double timeDelta, sBasic* vars, SpriteController* This);


public:
	bool isVisible;					// Enables or prevents drawing to the screen
	double  xCurr, yCurr, zCurr;	// Used to update location and layer of the object

	
	// Basic constructor functions
	SpriteController(){};
	SpriteController(Sprite* s, sBasic* gVars=0, int (*func)(double,sBasic*,SpriteController*)=0, int tState=0,int tFrame=0,int x=0,int y=0,int z=1){init(s, gVars, func, tState,tFrame,x,y,z);};

	
	// Basic access functions
	int width(){return sprite->getState(stateCurr)->getFrameRects()[(int)frameCurr].w;};
	int height(){return sprite->getState(stateCurr)->getFrameRects()[(int)frameCurr].h;};
	int getCurrentState(){return (int)stateCurr;}
	int getCurrentFrame(){return (int)frameCurr;}
	int getMaxFrames(){return sprite->getState(stateCurr)->getNumFrames();};
	double getFrameCurr(){return frameCurr;}
	double getFrameDelta(){return frameDelta;}
	sBasic* getGameVars(){return gameVars;}


	// Defined and commented in spritecontroller.cpp
	bool init(Sprite* s, sBasic* gVars = 0, int (*func)(double,sBasic*,SpriteController*) = 0, int tState=0,int tFrame=0,int x=0,int y=0,int z=0);
	~SpriteController();				
	void draw(SDL_Surface* screen);			// Draw the object to the screen
	bool isPixelTransparent(int x, int y);	// takes the xy coords on screen and returns true if the pixel is transparent
	int update(double d);					// Update based on timeslice in ms

	
	void setCurrentFrame(double i=0);	// basic set functions 
	void setCurrentState(int i=0);
	void setFrameDelta(double d=0.0f);
	void setStyle(sBasic* newVars, int (*func)(double,sBasic*,SpriteController*));
};

#endif
