#include "collision.h"

#define SDL_COLLIDE_MAX(a,b)	((a > b) ? a : b)	//returns the largest value passed
#define SDL_COLLIDE_MIN(a,b)	((a < b) ? a : b)	//returns the smallest value passed




//////////
// Returns true if the sprite is off the edge of the screen, false otherwise.
//
//////////

bool CollisionList::outOfBounds(SpriteController* c)
{
	if(c == 0)
	{
		return true;
	}

  	if(c->xCurr < (boundsBuffer*-1) || c->xCurr > screenW + boundsBuffer || c->yCurr < (boundsBuffer*-1) || c->yCurr > screenH + boundsBuffer)
	{
		return true;
	}
  	return false;
}



//////////
// Safely removes the sprite from the the first collision list.  
//	Returns true if it is found and removed, false otherwise.
//
//////////

bool CollisionList::removeSpriteA(SpriteController *d)
{
	a->beginning();
	do
	{
		if(a->display() == d)
		{
			a->remove();
			return true;
		}
	}while(a->next());
	return false;
}



//////////
// Safely removes the sprite from the the second collision list.  
//	Returns true if it is found and removed, false otherwise.
//
//////////

bool CollisionList::removeSpriteB(SpriteController *d)
{
	b->beginning();
	do
	{
		if(b->display() == d)
		{
			b->remove();
			return true;
		}
	}while(b->next());
	return false;
}




///////////////////////////////////////	
//SDL_CollidePixel
// Pixel perfect collision detection that uses bounding box checking.
//	If the bounding boxes collide then it calculates the area of overlap
//	between these bounding boxes.  Then every pixel in this area of 
//	collision is checked for transparency.  If the neither sprite is
//	transparent for a given pixel then a collision has been found.
//	Returns true on collision, false otherwise.
//
///////////////////////////////////////	

bool SDL_CollidePixel(SpriteController* a , SpriteController* b)
{
	

	// Get the opposite corners of the bounding boxes

	// a - bottom right coordinates
	int ax1 = (int)a->xCurr + a->width() - 1;
	int ay1 = (int)a->yCurr + a->height() - 1;
	
	// b - bottom right coordinates
	int bx1 = (int)b->xCurr + b->width() - 1;
	int by1 = (int)b->yCurr + b->height() - 1;

	// Check if bounding boxes intersect
	if((bx1 < a->xCurr) || (ax1 < b->xCurr))
		return false;
	if((by1 < a->yCurr) || (ay1 < b->yCurr))
		return false;

	// If the function has run this far there is at least a bounding box collision.
	// Find the area of intersection. 
	
	// Upper left corner
	int inter_x0 = SDL_COLLIDE_MAX(a->xCurr,b->xCurr);
	int inter_y0 = SDL_COLLIDE_MAX(a->yCurr,b->yCurr);

	// Lower right corner
	int inter_x1 = SDL_COLLIDE_MIN(ax1,bx1);
	int inter_y1 = SDL_COLLIDE_MIN(ay1,by1);			

	// Loop through all the pixels in the area of intersection
	for(int y = inter_y0 ; y <= inter_y1 ; y++)
	{
		for(int x = inter_x0 ; x <= inter_x1 ; x++)
		{
			// If a given pixel is not clear for both objects, we have a collision
			// Writen this way for speed.  If a is transparent there can be no collision.
			if(!(a->isPixelTransparent(x,y)))
			{
				if(!(b->isPixelTransparent(x,y)))
					return true;
			}
		}
	}
	return false;
}




//////////
// Generates a list of collisions.  Each collision contains an object from list
//	a and all of the objects from list b that collided with it.  
//	Returns true if any collisions are found, false otherwise.
//
//////////

bool CollisionList::checkCollision()
{
	// Be sure to start at the beginning.
	a->beginning();


	// For every object on listA
	for(int counter = 0; counter < a->length(); counter++, a->next())
	{
		// check bounds
		if(outOfBounds(a->display()))
		{
			oOBound->insert(a->display());
		}
		else
		{
			// If the object is within bounds, start a new list of sprite controllers.
			LinkedList<SpriteController>* list = new LinkedList<SpriteController>();
			
			
			// Starting with the first object in b
			b->beginning();

			// For every object in b
			for(int count = 0; count < b->length(); count++, b->next())
			{
				// Check for collisions and add b to the list.
				if(SDL_CollidePixel(a->display(), b->display()))
				{
					list->insert(b->display());
				}
			}

			// Collisions with a->display occured
			if(list->length())
			{
				// Create a collision object and store it.
				collisions->insert(new collision);

				// Store the values in the object that was just created
				collisions->display()->list = list;
				collisions->display()->main = a->display();
			}
			else
			{
				//No colisions so delete the empty list
				delete list;
			}
		}
	}

	// Check that all of the objects in list b are within bounds.
	b->beginning();
	int counter;
	for(counter = 0; counter < b->length(); counter++, b->next())
	{
		if(outOfBounds(b->display()))
		{
			oOBound->insert(b->display());
		}
	}
	
	// If collisions were found return true, false otherwise.
	return (collisions->length() > 0);
}