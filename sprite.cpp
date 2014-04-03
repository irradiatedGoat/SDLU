//sprite.cpp
#include "sprite.h"


//////////
// These are safe access functions.  These return 0 if the input is out of bounds.
//
//////////
State* Sprite::getState(int i)
{
	if(i < 0 || i > numStates)
		return 0;
	return &states[i];
}
int Sprite::getFrames(int state)
{
	if(state < 0 || state > numStates)
		return 0;
	return states[state].getNumFrames();
}



//////////
//Safe draw function.  Calls the draw function on the correct state passing the 
//  SDL surface, rect and frame number.
//
//////////
void Sprite::draw(SDL_Surface* screen, SDL_Rect* drawToRect, int currState,int currFrame)
{
	if(currState < 0 || currState > numStates)
		return;
	states[currState].draw(screen,drawToRect, currFrame);
}




bool Sprite::isPixelTransparent(int state, int frame, int x, int y)
{
	if(state < 0 || state > numStates)
		return true;

	return states[state].isPixelTransparent(frame, x, y);
}