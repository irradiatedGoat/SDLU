#include "datastruct.h"


node<element>* merge(node<element>* listOne, node<element>* listTwo)
{
	if(listOne == 0)
	{
		return listTwo;
	}
	else if(listTwo == 0)
	{
		return listTwo;
	}
	node<element>* temp = new node<element>();
	node<element>* returnVal = new node<element>();
	if(listOne->element->index > listTwo->element->index)
	{
		temp = listTwo;
		returnVal = listTwo;
		listTwo = listTwo->nex;
	}
	else if(listTwo->element->index >= listOne->element->index)
	{
		temp = listOne;
		returnVal = listOne;
		listOne = listOne->nex;
	}
	
	while(listOne != 0 && listTwo != 0)
	{

		if(listOne->element->index > listTwo->element->index)
		{
			temp->nex = listTwo;
			temp = temp->nex;
			listTwo = listTwo->nex;
		}
		else if(listOne->element->index <= listTwo->element->index)
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

node<element>* compare(node<element>* first, node<element>* last)
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
			if(first->element->index > last->element->index)
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
			node<element>* tempLast = first->nex;
			node<element>* tempFirst = first->nex->nex;
			
			tempLast->nex = 0;
			tempFirst->pre = 0;
			node<element>* listOne = compare(first, tempLast);
			node<element>* listTwo = compare(tempFirst, last);
			return merge(listOne, listTwo);
		}
	}
	return 0;
};

void* sortLinkedList(LinkedList<element>* temp)
{
	SortGhost<element>* g = new SortGhost<element>(temp);
	if(temp->length() > 19000)
	{
		node<element>* nextHead;
		node<element>* portion;
		node<element>* whole = 0;
		node<element>* cHead = g->head()->nex;
		node<element>* cTail = cHead;
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
	
	node<element>* temporary = g->head();
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

//////////////////////////
//  Sorting function for
//  LinkedLists<element>
//
//  slows down alot after 
//  the first thousand elements
//  wont do anything over 9593
//  elements
//////////////////////////
/*
void* sort(node<element>* head, node<element>* last)
{
	int loops = 0;
	do
	{
		cout << " loop: " << loops << endl;
		if(head == 0 || last == 0 || head->nex == last)
		{
			return 0;
		}
		if(head->element == 0)
		{
			while(head->element == 0)
			{
				head = head->nex;
			}
		}
		node<element> *current = head;	
		
	
		while(current->nex != last)
		{
			current = current->nex;
			if( current->element != 0)
			{
				if(head->element->index > current->element->index)
				{
					element* temp = current->element;
					current->element = head->element;
					head->element = temp;
				}
			}
		}
	
		head = head->nex;
		loops++;
	}while(head->nex != last);
};

void* sortLinkedList(LinkedList<element> *temp)
{
	if(temp->length() < 2)
	{
		return 0;
	}
	node<element> *begining = temp->head;
	node<element> *end = temp->tail;
	sort(begining, end);
};
*/
