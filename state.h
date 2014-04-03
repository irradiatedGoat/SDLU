#ifndef _STATE_H_
#define _STATE_H_

#include <SDL.h>
#include <iostream>

//////////////////////////////////////
//State.h
//
//  State holds the frames and the bitmap needed to render animation.
//  Current frame of animation and animation speed is handled on higher levels.
//  This draws whatever frame of animation it's told to draw by higher level objects.
//
//	0.1 Moved anim data from Adam's sprite.h here and cleaned up naming etc etc..
//
//////////////////////////////////////

class State
{
	int numFrames;				// total frames of animation
	SDL_Rect* lFrame;			// list of framing rectangles
	SDL_Surface* stateMap;		// bitmap that is divided up for frames
	bool* bitmask;				// bitmask for collision detection.  True for a colidable point.
	void buildMask();			// build bitmask for collision detection.  private for saftey.

public:

	// Basic constructors.
	State(SDL_Surface* sur, SDL_Rect* frame, int numberOfFrames){stateMap = sur; lFrame= frame; numFrames = numberOfFrames;};
	State(){numFrames=0;lFrame = NULL; stateMap = NULL;}

	// See state.cpp for detailed comments on these functions.
	~State();
	bool init(char* bitmapName, SDL_Rect* frames, int numberOfFrames,Uint8 r,Uint8 b, Uint8 g);
	bool init(char* bitmapName, SDL_Rect* frames, int numberOfFrames,Uint32 ColorKey);
	bool init(char* bitmapName, SDL_Rect* frames, int numberOfFrames);
	void draw(SDL_Surface* screen, SDL_Rect* target,int thisFrame);
	bool isPixelTransparent(int thisFrame, int x , int y);



	
	// Accessor functions
	SDL_Rect* getFrameRects(){return lFrame;}
	SDL_Surface* getStateMap(){return stateMap;}
	int getNumFrames(){return numFrames;}

};





#endif
