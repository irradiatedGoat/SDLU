#include "keyhandler.h"

//////////
// process SDL messages without mouse handling
//
//////////
void KeyHandler::process(SDL_Event& event)
{
	// Process SDL key event.
	if(event.type == SDL_KEYDOWN)
	{
		int curr = event.key.keysym.sym;			// a key was pressed
		keys[curr].down = true;						// actuall state of the key
		keys[curr].switched = !keys[curr].switched; // cycles only on key downs
		keys[curr].lastPressed = SDL_GetTicks();	// reset the time 
	}
	if(event.type == SDL_KEYUP)
	{
		keys[event.key.keysym.sym].down = false;	// button is no longer pressed
	}
	
};



//////////
// Process SDL messages with mouse handling
//
//////////
void KeyHandler::processM(SDL_Event& event)
{
	// Process SDL key event
	if(event.type == SDL_KEYDOWN)
	{
		// a key was pressed
		int curr = event.key.keysym.sym;
		keys[curr].down = true;								// actuall state of the key
		keys[curr].switched = !keys[curr].switched;			// cycles only on key downs
		keys[curr].lastPressed = systemTimer.getRunTime();	// reset the time 
	}
	if(event.type == SDL_KEYUP)
	{
		keys[event.key.keysym.sym].down = false;	// button is no longer pressed
	}


	// Process mouse movement
	if(event.type == SDL_MOUSEMOTION)
	{
		// Throws updated mouse possition and movement on the queue
		mouse->insert(new mouseMsg(event.motion.x,
					   event.motion.xrel, 
					   event.motion.y, 
					   event.motion.yrel));
	}


	// Process mouse buttons
	if(event.type == SDL_MOUSEBUTTONDOWN || event.type ==SDL_MOUSEBUTTONUP)
	{
		// check to see if a button went up or down
		bool temp = false;
		if(event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			temp = true;
		}
		// change the proper bool
		switch(event.button.button)
		{
			case SDL_BUTTON_LEFT:
			left = temp;
			break;
			case SDL_BUTTON_RIGHT:
			right = temp;
			break;
			case SDL_BUTTON_MIDDLE:
			mid = temp;
			break;
		}
	}
	
};



//////////
//	Stores the switched keys.
//
//////////
key* KeyHandler::exportKeyState()
{
	key* temp = new key[NUMBEROFKEYS];					// Generate the list of keys to export
	for(int count = 0; count < NUMBEROFKEYS; count++)	// For each, export the value into the new list
	{
		temp[count].down = keys[count].down;
		temp[count].switched = keys[count].switched;
		temp[count].lastPressed = keys[count].lastPressed;
	}
	return temp;										// Return the new copy.
};




//////////
//Reloads an old keystate over the current keystate
//
//////////
void KeyHandler::importKeyState(key* iKey)
{
	for(int count = 0; count < NUMBEROFKEYS; count++)		//For each of the keys, copy the input into the internal.
	{
		keys[count].down = iKey[count].down;
		keys[count].switched = iKey[count].switched;
		keys[count].lastPressed = iKey[count].lastPressed;
	}
};



//////////
//Resets everything to object construction state.
//
//////////
void KeyHandler::zeroAll()
{
	left = false;					// All mouse buttons are not pressed.
	mid = false;
	right = false;
	if(mouse != 0)					// Empty the mouse queue
	{
		while(mouse->length())
		{
			delete mouse->remove();
		}
	}
	else							// If there is no mouse queue, make one.  (Mainly used by the constructor)
	{
		mouse = new Queue<mouseMsg>();
	}
	
	for(int count = 0; count < NUMBEROFKEYS; count++)
	{								// Zero all keys
		keys[count].zero();
	}
};



//////////
//Contsructor
//
//////////
KeyHandler::KeyHandler()
{
	mouse = 0;	//Tricks zeroAll into making a new mouse queue
	zeroAll();
}



//////////
//Deconstructor
//
//////////
KeyHandler::~KeyHandler()
{
	// Mouse queue is the only thing that uses pointers and wont be destroyed automagically.
	if(mouse != 0)
	{
		while(mouse->length())
		{
			delete mouse->remove();
		}
		delete mouse;
	}
}
