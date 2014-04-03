#ifndef _LOADER_H_
#define _LOADER_H_

#include <SDL.h>
#include <iostream>
#include "reference.h"
#include "window.h"
#include "interpreter.h"
#include "font.h"

//////////////////////////////////////
//Loader.h
//  Loader opens a text file and uses it to build all of the rectangles and load all of 
//  the bitmaps used to create every sprite in the program as a template.  Each template 
//  consists of one or more states that a sprite can be in.  Each state contains a 
//  bitmap that holds all of the images used in a given animation and each of the 
//  rectangles used to outline the frames in the animation sequence.
//  The end result is a Sprite class that contains several different animations that can 
//  be activated by changing an integer in the sprite class.
//
//  Ex:	If you have a character on screen that can walk left or right
//		you can have a walking left animation, a walking right 
//		animation and a standing animation and change animation easily.
//////////////////////////////////////

class Loader
{
public:
	SDL_Surface* screen;
	bool loadSpriteControllers(CScript *scr);
	bool loadSprites(CScript *scr);
	bool loadSprite(CScript *scr);
	bool loadState(CScript *scr, State *state);
	bool loadStateGroup(CScript *scr);
	bool loadStateGroups(CScript *scr);
	bool loadRect(CScript *scr, SDL_Rect* rect);
	bool loadRectGroup(CScript *scr);
	bool loadRectGroups(CScript *scr);
	bool loadFonts(CScript *scr);
	bool loadFont(CScript *scr);
	referenceTable<Font> fontSet;
	referenceTable<SDL_Rect> rectGroups;
	referenceTable<int> rectGroupSize;
	referenceTable<State> stateGroups;
	referenceTable<int> stateGroupSize;
	referenceTable<Sprite> sprites;
	referenceTable<SpriteController> sControllers;
	CScript* root;

	Loader(){root = new CScript;}
	Loader(SDL_Surface* scr){screen = scr; root = new CScript;}
	bool Load(char* filename);
};


#endif
