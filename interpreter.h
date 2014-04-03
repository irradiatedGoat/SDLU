#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <string>
#include <iostream>
#include <fstream>
#include "datastruct.h"

class CScript
{
private:
//		char* cursePastBrackets(char* string);
public:
	CScript(){children=NULL;value=NULL;}
	bool init(char* scr);
	//!takes care of loading a configuration script
	bool Load(char* fname);	
	//!returns a pointer to first child
	CScript* findChild(char* childTag,bool reset=false);

	//!either the tag or the argument
	char* value;
	//!list of subscripts
	LinkedList<CScript> *children;
};



#endif
