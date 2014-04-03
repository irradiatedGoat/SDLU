
#include "window.h"
Window::Window(SDL_Surface* scr)
{
	spriteList = new LinkedList<SpriteController>();
	exitingSprites = new LinkedList<SpriteController>();
	screen = scr;
	sorted = false;

}
void Window::addSprite(SpriteController* sp)
{
	if(spriteList!=NULL)
	{
		sorted = false;
		spriteList->insert(sp);
	}
}
bool Window::removeSprite(SpriteController* sp)
{
	if(spriteList == 0 || sp == 0)
	{
		return false;
	}
	if(spriteList->length() == 0)
	{
		return false;
	}
	spriteList->beginning();
	do
	{
		if(spriteList->display() == sp)
		{
			spriteList->remove();
			return true;
		}
	}while(spriteList->next());
	return false;
}
bool Window::beginExiting(SpriteController* sp)
{
	if(exitingSprites == 0 || sp == 0)
	{
		return false;
	}
	spriteList->beginning();
	do
	{
		if(spriteList->display() == sp)
		{
			exitingSprites->beginning();
			do
			{
				if(exitingSprites->display() == sp)
				{
					return false;
				}
			}while(exitingSprites->next());
			exitingSprites->insert(sp);
			return true;
		}
	}while(spriteList->next());
	return false;
}


bool Window::init(SDL_Surface* scr)
{
	spriteList = new LinkedList<SpriteController>();
	screen = scr;
	return true;
}


bool Window::update(double timeChunk)
{
	int spriteStatus;

	// start at the begining of the sprite list
	if(spriteList->beginning())
	{
		do
		{
			// update it and catch it's status it's status
			spriteStatus = (spriteList->display())->update(timeChunk);
			if(spriteStatus == DESTROY)
			{
				// If it's ready to exit the program, throw it into the garbage queue and let the registry catch it.
				exitingSprites->insert(spriteList->display());
			}

		// move on to the next sprite
		}while(spriteList->next());	
	}
	return true;
}




void Window::draw()
{
	// Start at the beginning of the sprite list
	if(spriteList->beginning())
	{
		do
		{
			// draw the sprite
			spriteList->display()->draw(screen);

		// move on to the next sprite
		}while(spriteList->next());	
	}
}

node<SpriteController>* merge(node<SpriteController>* listOne, node<SpriteController>* listTwo)
{
	if(listOne == 0)
	{
		return listTwo;
	}
	else if(listTwo == 0)
	{
		return listTwo;
	}
	node<SpriteController>* temp;
	node<SpriteController>* returnVal;
	if(listOne->element->zCurr > listTwo->element->zCurr)
	{
		temp = listTwo;
		returnVal = listTwo;
		listTwo = listTwo->nex;
	}
	else if(listTwo->element->zCurr >= listOne->element->zCurr)
	{
		temp = listOne;
		returnVal = listOne;
		listOne = listOne->nex;
	}
	
	while(listOne != 0 && listTwo != 0)
	{
		if(listOne->element->zCurr > listTwo->element->zCurr)
		{
			temp->nex = listTwo;
			temp = temp->nex;
			listTwo = listTwo->nex;
		}
		else if(listOne->element->zCurr <= listTwo->element->zCurr)
		{
			temp->nex = listOne;
			temp = temp->nex;
			listOne = listOne->nex;
		}

	}
	if(listTwo == 0)
	{
		temp->nex = listOne;
	}
	else if(listOne == 0)
	{
		temp->nex = listTwo;
	}
	return returnVal;
};

node<SpriteController>* compare(node<SpriteController>* first, node<SpriteController>* last)
{
	if(first != 0 && last != 0)
	{
		if(first == last)
		{
			first->nex = 0;
			first->pre = 0;
			return first;
		}
		if(first->nex == last)
		{
			if(first->element->zCurr > last->element->zCurr)
			{
				first->nex = 0;
				first->pre = last;
				last->nex = first;
				last->pre = 0;
				return last;
			}
			else
			{
				first->pre = 0;
				last->nex = 0;
				return first;
			}
		}
		else
		{
			node<SpriteController>* tempLast = first->nex;
			node<SpriteController>* tempFirst = first->nex->nex;
			
			tempLast->nex = 0;
			tempFirst->pre = 0;
			node<SpriteController>* listOne = compare(first, tempLast);
			node<SpriteController>* listTwo = compare(tempFirst, last);
			return merge(listOne, listTwo);
		}
	}

	return 0;
};

void* sortLinkedList(LinkedList<SpriteController>* temp)
{
	SortGhost<SpriteController>* g = new SortGhost<SpriteController>(temp);
	if(temp->length() > 19000)
	{
		node<SpriteController>* nextHead;
		node<SpriteController>* portion;
		node<SpriteController>* whole = 0;
		node<SpriteController>* cHead = g->head()->nex;
		node<SpriteController>* cTail = cHead;
		while(cTail != g->tail()->pre && cTail)
		{
			cTail = cHead;
			for(int counter = 0; cTail && counter < 10000; counter ++)
			{
				cTail = cTail->nex;
			}
			if(cTail == 0 && cHead != g->tail()->pre)
			{
				cTail = g->tail()->pre;
			}
			nextHead = cTail->nex;
			cTail->nex = 0;
			portion = compare(cHead, cTail);
			whole = merge(whole, portion);
			cHead = nextHead;
		}
		g->head()->nex = whole;
	}
	else
	{
		g->head()->nex = compare(g->head()->nex, g->tail()->pre);
	}
	
	node<SpriteController>* temporary = g->head();
	while(temporary->nex)
	{
		temporary ->nex->pre = temporary;
		temporary = temporary->nex;
	}
	temporary->nex = g->tail();
	g->tail()->pre = temporary;
	g->current(g->head()->nex);
	return 0;
};


void Window::ZOrderSort()
{
	if(!sorted)
	{
		sortLinkedList(spriteList);
		sorted = true;
	}
};

