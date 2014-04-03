#ifndef _REGISTRY_H_
#define _REGISTRY_H_
#include "window.h"
#include "keyhandler.h"
#include "interpreter.h"

#define MAX_SPRITES 500
#define LISTA 1337
#define LISTB 1338

class Registry
{
	Window* w;
	KeyHandler* k;	// not used at the moment but could be incorporated later.
	
public:
	Registry(Window* wN, KeyHandler* kN){w = wN; k = kN;};
	bool add(SpriteController* s);
	bool remove(SpriteController* s);
	bool beginExiting(SpriteController* s);
	void collectGarbage();
};
#endif
