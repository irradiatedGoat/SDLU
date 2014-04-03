#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "state.h"

//////////////////////////////////////
//State.h
//
//  Sprite contains a collection of states for a given object.
//  Current frame of animation and animation speed is handled on higher levels.
//  This selects the state to draw and passes the screen, rect, and frame
//  down to that state.
//
//////////////////////////////////////
class Sprite
{
private:
	State* states;					// Pointer to an array of states.
	int numStates;					// Number of states in the array.
	
public:

	// Basic constructors and initializers
	Sprite(){};
	Sprite(State* nStates, int numberOfStates){init(nStates, numberOfStates);};  
	~Sprite(){};
	void init(State* nStates, int numberOfStates){states = nStates; numStates = numberOfStates;};
	
	// Basic accessor function
	int getNumberOfStates(){return numStates;};
	
	// Defined and commented in state.cpp
	void draw(SDL_Surface* screen, SDL_Rect* drawToRect,int currState,int currFrame);
	bool isPixelTransparent(int state, int frame, int x, int y);
	State* getState(int i=0);
	int getFrames(int state);
};

#endif
