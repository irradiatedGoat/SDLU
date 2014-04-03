#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "datastruct.h"
#include "spritecontroller.h"

//////////////////////////////////////
//Collision.h
//
//  CollisionList is a rapid detection and storage mechanisim for collisions
//	and out of bounds objects.  It contains two lists, a and b.  Objects in
//	list a are checked against objects of list b.  If a collision is found,
//	a collision struct is created to contain the object from list a and all
//	of the objects from list b that collided with it.
//	Both collisions and out of bounds objects are stored in lists (collisions 
//	and oOBound respectivly) to be dealt with by other systems.  
//
//////////////////////////////////////

// basic container class for tracking collisions
struct collision
{
	SpriteController *main;
	LinkedList<SpriteController> *list;
};

class CollisionList
{
	LinkedList<SpriteController> *a;	// primary list
	LinkedList<SpriteController> *b;	// secondary list
	int boundsBuffer,					// the pixels off the edges of the screen before something is out of bounds.
		screenW,						// screen width
		screenH;						// screen height

public:
	LinkedList<collision>* collisions;
	LinkedList<SpriteController>* oOBound;

	// basic constructor destrctor pair
	CollisionList(int sW = 640, int sH = 480, int bb = 800){a = new LinkedList<SpriteController>(); b = new LinkedList<SpriteController>(); collisions = new LinkedList<collision>(); oOBound = new LinkedList<SpriteController>(); boundsBuffer = bb; screenW = sW; screenH = sW;};
	~CollisionList(){};

	// These are responsible for populating collisions and oOBound and are commented in collision.cpp
	bool checkCollision();					
	bool outOfBounds(SpriteController* a);	

	// Basic Add/Remove functions.  Removes functions are safe.
	bool removeSpriteA(SpriteController *d);
	bool removeSpriteB(SpriteController *d);
	void addSpriteA(SpriteController *d) { a->insert(d); };
	void addSpriteB(SpriteController *d) { b->insert(d); };
};

#endif
