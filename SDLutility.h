#ifndef _SDLUTILITY_H_
#define _SDLUTILITY_H_
/*
	Includes and dependencies (see each file for more info.)
*/
#include "datastruct.h"			// stand-alone
#include "reference.h"			// stand-alone
#include "keyhandler.h"			// datastruct.h, SDL.h
#include "timer.h"				// SDL.h
#include "state.h"				// SDL.h
#include "sprite.h"				// state.h
#include "spritecontroller.h"	// sprite.h
#include "window.h"				// spritecontroller.h, datastruct.h
#include "registry.h"			// window.h, collision.h, keyhandler.h, interpreter.h
#include "interpreter.h"		// datastruct.h
#include "loader.h"				// refrence.h, window.h, interpreter.h
#include "font.h"				// sdl.h, sdl_ttf.h
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    21		//needs to be changed in main

static double CurTime=0.0f;
static double DeltaTime=0.0f;
static double LastTime=0.0f;


//helper function for the timer wraping the SDL timer
//double Delta_Time(void);
//returns the framerate	(must be run every loop)
double frameRate();
void frameAdvance();
//helper loading function
SDL_Surface* SDLutility(char* windowName, int windowWidth, int windowHeight);
char* intToStr(int value, char* string, int length);
#endif