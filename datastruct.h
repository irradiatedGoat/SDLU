#ifndef _DataStruct_h_
#define _DataStruct_h_
// a list of all the classes in this file: (all line numbers are aproximate..)
template <class T>	// line 40
class node;		//for doubly linked lists

template <class T>	// line 69
class sNode;		//for singly linked lists (not used)



template <class T>	// line 96
class LinkedList;	// basic linked list class. fully functional

template <class T>	// line 301
class Queue;		// basic FIFO datastruct

template <class T>	// line 453
class Stack;		// basic FILO datastruct

template <class T>	// line 645
class iArray;		// an array that simplifies adding and removing

//////////////////////// Sorting classes ///////////////////////
class element;		// dummy class to keep the compiler happy and to serve as an example
			// of how to make the sort work.  starts on line 721.

template<class T>	// line 745
class SortGhost;	// helper function for the sort function.

template<class T>
class QueueSortGhost;// line ~~
					// helper function for sort function with a queue
/*
	About the sort used here:  This sort is designed for use ONLY with the linked list class.  Modifying it to sort a Queue or stack would not be difficult but I dont have any need to.   For sorting the iArray a new function will need to be writen that can sort arrays.
*/


//////////////////////////
// template node for doubly linked lists
//////////////////////////

template <class T>
class node
{
public:
	T* element;
	node* nex;
	node* pre;

	node()
	{
		element = 0;
		nex = 0;
		pre = 0;
	};
	~node()
	{
		nex = 0;
		pre = 0;
		delete nex;
		delete pre;
	};
};



//////////////////////////
// template node for singly linked lists
//////////////////////////

template <class T>
class sNode
{
public:
	T *element;
	sNode *nex;

	sNode()
	{
		element = 0;
		nex = 0;
	};
	~sNode()
	{
		nex = 0;
		delete nex;
	};
};







template <class T>
class LinkedList
{
private:
	node<T>* head;
	node<T>* current;
	node<T>* tail;
	int len;
	int cur;
public:
	LinkedList()
	{
		head = 0;
		current = 0;
		tail = 0;
		len = 0;
		cur = -1;
	};
	~LinkedList()
	{
		if(head != 0)
		{
			node<T>* temp = head;
			T* temp1;
			while(head->nex != 0)
			{ 
				head = head->nex;
				temp1 = head->element;
				if(temp1 != 0)
				{
					delete temp1;
				}
				delete temp;
				temp = head;
			}
			delete temp;
		}
	}


	void insert(T* newElem)
	{
		
		if(len == 0)
		{
			current = new node<T>();
			head = new node<T>();
			tail = new node<T>();
			current->element = newElem;
			current->nex = tail;
			tail->pre = current;
			current->pre = head;
			head->nex = current;
		}
		else
		{
			node<T>* temp = new node<T>();
			temp->element = newElem;
			temp->nex = current->nex;
			temp->pre = current;
			current->nex->pre = temp;
			current->nex = temp;
			current = temp;
		}
		len++;
		cur++;
	}


	T* replace(T* newElem)
	{
		if(len == 0)
			return 0;
		T* temp = 0;
		temp = current->element;
		current->element = newElem;
		return temp;
	}


	T* remove()
	{
		T* returned;
		if(len == 0)
			return 0;
		else if(len == 1)
		{
			returned = current->element;
			delete head;
			delete current;
			delete tail;
			head = 0;
			current = 0;
			tail = 0;
			
		}
		else
		{
			node<T>* temp = current;
			returned = current->element;
			current->nex->pre = current -> pre;
			current->pre->nex = current -> nex;
			if(current->nex == tail)
				current = current->pre;
			else
				current = current->nex;
			
			delete temp;
		}
		len--;
		if(cur!= 0)
			cur--;
		return returned;
	};


	T* display()
	{
		
		if(current != 0)
		{
			return current->element;
		}
		return 0;
	}

	bool next()
	{
		if(len < 1)
		{
			return false;
		}
		if(current->nex == tail)
		{
			return false;
		}
		current = current->nex;
		cur++;
		return true;
	}

	bool prev()
	{
		if( len < 1)
		{
			return false;
		}
		if( current->pre == head)
		{
			return false;
		}
		current = current->pre;
		cur--;
		return true;
	}


	bool beginning()
	{
		if(len < 1)
		{
			return false;
		}
		current = head->nex;
		cur= 0;
		return true;
	}



	bool end()
	{
		if(len < 1)
		{
			return false;
		}
		current = tail->pre;
		cur = len -1;
		return true;
	}
	bool goTo(int i)
	{
		if( i < len)
		{
			current = head->nex;
			for(cur = 0; cur < i; cur++)
			{
				current = current->nex;
			}
			return true;
		}
		return false;
	}

	int currentElement()
	{
		return cur;
	}
	int length()
	{
		return len;
	}

	friend class SortGhost<T>;
};


template <class T>
class Queue
{
private:

	node<T>* head;
	node<T>* current;
	node<T>* tail;
	int len;
public:
	Queue()
	{
		head = 0;
		current = 0;
		tail = 0;
		len = 0;
	}

	~Queue()
	{
		if(head != 0)
		{
			node<T>* temp = head;
			while(head->nex != 0)
			{ 
				head = head->nex;
				delete temp;
				temp = head;
			}
			delete temp;
		}
	}

	void insert(T* newElem)
	{
		if(len == 0)
		{
			current = new node<T>();
			head = new node<T>();
			tail = new node<T>();
			current->element = newElem;
			current->nex = tail;
			tail->pre = current;
			current->pre = head;
			head->nex = current;
		}
		else
		{
			node<T>* temp = new node<T>();
			temp->element = newElem;
			temp->nex = tail;
			temp->pre = tail->pre;
			tail->pre->nex = temp;
			tail->pre = temp;
		}
		len++;
	}

	T* remove()
	{
		T* temp;
		if(len == 0)
		{
			return 0;
		}
		else if(len == 1)
		{
			temp = head->nex->element;
			node<T>* deleter = head->nex;
			delete head;
			delete deleter;
			delete tail;
			head = 0;
			tail = 0;
			current = 0;
		}
		else
		{
			if(head->nex == current)
			{
				current = current->nex;
			}
			temp = head->nex->element;
			node<T>* deleter = head->nex;
			head->nex = head->nex->nex;
			head->nex->pre = head;
			delete deleter;
		}
		len--;
		return temp;
	}

	T* display()
	{
		if(len == 0)
		{
			return 0;
		}
		return current->element;
	}
	T* replace(T* newElem)
	{
		T* temp = current->element;
		current->elment = newElem;
		return temp;
	}
	bool next()
	{
		if(head != 0)
		{
			if(head->nex != current)
			{
				current= current->pre;
				return true;
			}
		}
		return false;
	}
	bool prev()
	{
		if(head != 0)
		{
			if(current != tail->pre)
			{
				current =current->nex;
				return true;
			}
		}
		return false;
	}
	bool beginning()
	{
		if(head != 0)
		{
			current = head->nex;
			return true;
		}
		return false;
	}
	bool end()
	{
		if(tail != 0)
		{
			current = tail->pre;
			return true;
		}
		return false;
	}
	int length()
	{
		return len;
	}

	friend class QueueSortGhost<T>;
};



template <class T>
class Stack
{
private:
	node<T>* head;
	node<T>* current;
	node<T>* tail;
	int len;
public:
	Stack()
	{
		head = 0;
		current = 0;
		tail = 0;
		len = 0;
	}
	~Stack()
	{
		if(head != 0)
		{
			
			node<T>* temp = head;
			
			while(temp->pre != 0)
			{
				head = temp;
				temp = head->pre;
				delete head;
			}
			delete temp;
			head = 0;
			current = 0;
			tail = 0;
			len = 0;
		}
	}
	void insert(T* newElem)
	{
		if(len == 0)
		{
			current = new node<T>();
			head = new node<T>();
			tail = new node<T>();
			current->element = newElem;
			current->pre = tail;
			tail->nex = current;
			current->nex = head;
			head->pre = current;
		}
		else
		{
			node<T>* temp = new node<T>();
			temp->element = newElem;
			temp->nex = head;
			temp->pre = head->pre;
			head->pre->nex = temp;
			head->pre = temp;
			current = temp;
		}
		len++;
	}
	T* remove()
	{
		T* temp;
		if(len == 0)
		{
			return 0;
		}
		
		else if(len == 1)
		{
			temp = head->pre->element;
			delete head->pre;
			delete head;
			delete tail;
			head = 0;
			tail = 0;
			current = 0;	
		}
		else 
		{
			temp = head->pre->element;
			node<T>* deleter = head->pre;
			if(current == head->pre)
			{
				current = head->pre->pre;
			}
			head->pre = head->pre->pre;
			head->pre->nex = head;
			delete deleter;
		}
		len --;
		return temp;
	}
	T* unstack()
	{
		T* returnVal;
		node<T>* deleter;
		if(len > 1)
		{
			len--;
			returnVal = current->element;
			if(current->pre != tail)
			{
				current = current->pre;
				deleter = current->nex;
				current->nex = current->nex->nex;
				current->nex->pre = current;
				delete deleter;
			}
			else
			{
				current = current->nex;
				deleter = current->pre;
				current->pre = current->pre->pre;
				current->pre->nex = current;
				delete deleter;
			}
		}
		else if(len == 1)
		{
			returnVal = remove();
		}
		else
		{
			return 0;
		}
		return returnVal;

	}
	T* display()
	{
		if(head != 0)
		{
			return current->element;
		}
		return 0;
	}
	bool next()
	{
		if(head!= 0)
		{
			if(current->nex != head)
			{
				current = current->nex;
				return true;
			}
		}
		return false;
	}
	bool prev()
	{
		if(head!= 0)
		{
			if(current->pre != tail)
			{
				current = current->pre;
				return true;
			}
		}
		return false;
	}
	bool bottom()
	{
		if(head!=0)
		{
			current = tail->nex;
			return true;
		}
		return false;
	}

	bool top()
	{
		if(head!=0)
		{
			current = head->pre;
			return true;
		}
		return false;
	}
	int length()
	{
		return len;
	}
};


/////////////////////////////
//	basicly a wrapper class for an array.  handles insertion and removal of items
//	without having to deal with shifting.  not as safe as a lnked list but not as slow :)
/////////////////////////////
template <class T>
class iArray
{
	int growth;
	int curSize;
	void expand()
	{
		size = growth + size;
		T** temp = new T[size];
		int counter;
		for(counter = 0; counter < curSize;  counter++)
		{
			temp[counter] = array[curSize];
		}
		for(counter = curSize; counter < size; counter++)
		{
			temp[counter] = 0;
		}
	}
public:
	int size;
	T** array;
	iArray(int s, int g)
	{
		size = s;
		growth = g;
		curSize = 0;
		array = new T[size];
		for(int counter = 0; counter < size; counter++)
		{
			array[counter] = 0;
		}
	}
	void add(T* newItem)
	{
		if(curSize == size)
		{
			expand();
		}
		array[curSize] = newItem;
		curSize++;
	}
	void add(T* newItem, int location)
	{
		if(curSize == size)
		{
			expand();
		}
		for(int temp = curSize-1; temp >= location; temp--)
		{
			array[temp+1] = array[temp];
		}
		array[location] = newItem;
		curSize ++;
	}
	T* remove(int location)
	{
		if(location >= curSize)
		{
			return 0;
		}
		T* temp = array[location];
		for(int counter = location; counter < curSize; counter++)
		{
			array[counter] = array[counter+1];
		}
		curSize --;
		return temp;
	}
};



//////////////////////////
//	Example class to show how to setup the sort function
/////////////////////////

class element
{
public:
	element(int i, void* v)
	{
		index = i;
		elem = v;
	}
	void* elem;
	int index;
};

///////////////////////////
// this is a demon class to help the sort function work..
// ignore it unless you want to see the mechanics of the 
// merge sort the is being used.
///////////////////////////

template<class T>
class SortGhost
{
private:
	LinkedList<T>* list;
public:
	SortGhost(LinkedList<T>* l){list = l;};
	node<T>* head(){return list->head;}
	node<T>* tail(){return list->tail;}
	node<T>* current(){return list->current;}
	void current(node<T>* t){list->current = t;}

};

template<class T>
class QueueSortGhost
{
private:
	Queue<T>* list;
public:
	QueueSortGhost(Queue<T>* l){list = l;};
	node<T>* head(){return list->head;}
	node<T>* tail(){return list->tail;}
	node<T>* current(){return list->current;}
	void current(node<T>* t){list->current = t;}
};

#endif
