#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "spritecontroller.h"
#include "datastruct.h"

//////////////////////////////////////
//Window.h
//
//  Window is the basic wrapper class for the SDL_Surface that controls the screen
//  and system for updateing all spriteControllers being drawn to the screen.  It 
//  also maintains a layer system drawing some sprites before others.
//
//////////////////////////////////////

///////////
// Sorting functions that control which sprites are drawn first.
//
///////////
node<SpriteController>* merge(node<SpriteController>* listOne, node<SpriteController>* listTwo);
node<SpriteController>* compare(node<SpriteController>* first, node<SpriteController>* last);
void* sortLinkedList(LinkedList<SpriteController>* temp);




class Window
{

	bool sorted;									// Signals that a new object has been added and the list should be resorted
	SDL_Surface* screen;							// The screen that everything is drawn to
	LinkedList<SpriteController> *spriteList;		// The list of objects that are being updated by the window manager
public:
	LinkedList<SpriteController>* exitingSprites;	// Objects that are running through exit animation and are about to be removed


	// These functions are defined and commented in window.cpp
	Window(SDL_Surface* scr = 0);					// Constructor
	bool init(SDL_Surface* scr);					// Initializer
	void addSprite(SpriteController *sp);			// Addes a new object
	bool removeSprite(SpriteController *sp);		// Removes an object directly from the draw queue
	bool beginExiting(SpriteController *sp);		// Removes an object from draw queue and places it in the exiting queue
	bool update(double timeChunk);
	void ZOrderSort();
	void draw();
	int length(){return spriteList->length();}
};
#endif
