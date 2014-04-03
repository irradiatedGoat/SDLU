#ifndef _KEYHANDLER_H_
#define _KEYHANDLER_H_
#include <SDL.h>
#include "datastruct.h"
#include "timer.h"
#define NUMBEROFKEYS 322		// thats right kids sdl has 276 keys (Not sure why, or why I went over that. Extras for you!)



//////////////////////////////////////
//Keyhandler.h
//	Keyhandler wraps SDLs key and mouse functions within SDL.  The switched option of each key
//	is the most useful feature from this set of classes.  It is also possible to export the 
//  set of keys that are being held down when the game is paused.
//  
//////////////////////////////////////


// holding structure for mouse movement messages
struct mouseMsg
{
	mouseMsg(int x, int xA, int y, int yA){xC = x; xR = xA; yC = y; yR = yA;};
	int xC;		// current x value
	int xR;		// x value realitive to the previous x value
	int yC;		// current y
	int yR;		// y realitive to previous
};

// holding structure for key information
class key
{
public:
	bool down;			// keys current state
	bool switched;		// switches only on key press (press the key once for true twice for false)
	int lastPressed;	// sdl time of last key press
	key(){zero();};
	void zero(){down = 0; switched = 0; lastPressed = 0;}; // constructor reset
};


class KeyHandler
{
public:
	key keys[NUMBEROFKEYS];				// keyboard keys
	bool left, mid, right;				// mouse buttons
	Queue<mouseMsg>* mouse;				// queue for mouse movement updates

	KeyHandler();
	~KeyHandler();
	void process(SDL_Event& event);		// key handling
	void processM(SDL_Event& event);	// key and mouse handling
	key* exportKeyState();				// saves the current key state 
	void importKeyState(key* iKey);		// loads a saved key state
	void zeroAll();						// constructor level reset
};
#endif
