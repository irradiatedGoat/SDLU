#include "registry.h"
bool Registry::add(SpriteController* s)
{
	if(w != 0)
	{
		w->addSprite(s);
		return true;
	}
	return false;
}

bool Registry::remove(SpriteController* s)
{
	if(w != 0)
	{
		
		// check the exiting sprites to make sure that the object isn't there
		w->exitingSprites->beginning();
		do
		{
			if(w->exitingSprites->display() == s)
			{
				w->exitingSprites->remove();
			}
		}while(w->exitingSprites->next());


		// Remove the sprite from the window
		if(w->removeSprite(s))
		{
			// object removed successfully
			return true;
		}
	}
	return false;
}

bool Registry::beginExiting(SpriteController* s)
{
	return w->beginExiting(s);
}

void Registry::collectGarbage()
{
	SpriteController* s;
	// clear exiting sprites
	while(w->exitingSprites->length())
	{
		s = w->exitingSprites->remove();
		remove(s);
		delete s;
	}
	
}