#ifndef _REFERENCE_H_
#define _REFERENCE_H_
#include <string>
#include <vector>

//////////////////////////////////////
//Refrence.h
//
//	Refrence table object allows for the pairing of names with 
//  templated values.
//  No error checking is done to be sure that any name or value is
//  valid.
//
////////////////////////////////////// 

template<class T>
class referenceTable
{
private:
	std::vector<T*> object;		// values being stored
	std::vector<char*> name;	// name for each value
public:
	void addReference(char* n, T* value)
	{
		object.push_back(value);
		name.push_back(n);
	}
	T* lookup(char *c)
	{
		// Search through the names registered for the one given.
   		for(int i=0; i < name.size();i++)
   		{
			// Return the associated value if one is found.
			if(strcmp(name[i],c)==0)
				return object[i];		
   		}
		// If nothing is found return null.
		return NULL;
	}
};



#endif
