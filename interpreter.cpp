#include "interpreter.h"
using namespace std;

bool CScript::Load(char* fname)
{
	ifstream f;
	f.open(fname,ios::in|ios::ate);	//open and set initial pos at eof
	if(!f.is_open())
	{
		cerr << "Error: script file " << fname << " not found!" << endl;
		return false;
	}
	
	long size = f.tellg();			//get current numerical location(file size)
  	f.seekg (0, ios::beg);
 	char *buffer = new char [size];		//make buffer of that size
  	f.read (buffer, size);			//copy whole script into memory
	f.close();

	if(!init(buffer))
	{
		cerr << "Error: script file " << fname << " could not be parsed.  Check your syntax." << endl;
		return false;
	}

	if(children!=NULL)				//safety check
	{

	}
	else	//if children was NULL then no script was actually loaded at all for that file
	{
		cerr << "No script found for at file " << fname << "." << endl;
		return false;
	}
	cerr << "Script " << fname << " successfully loaded." << endl;
	return true;		//everything went through alright
}

char* cursePastBrackets(char* string)
{
	char* tmp=string;
	while(*tmp!='{')		//make sure we are actually started at the bracket
	{
		tmp++;
		if(*tmp=='\0')
			return tmp;
	}

	int bracketCount=1;
	tmp++;
	if(*tmp=='\0')	//standard NULL check on tmp doesnt work
			return tmp;	//will check against *tmp returning NULL would segfault
	while(bracketCount>0)
	{
		if(*tmp=='{')
		{
			bracketCount++;
		}
		else if(*tmp=='}')
		{
			bracketCount--;
		}
		tmp++;
		if(*tmp=='\0') //premature eos(probably missing bracket)
		{
			return tmp;	//will check against *tmp returning NULL would segfault
		}
	}
	return tmp;
}

char* safeGoto(char s, char* string)
{
	char* tmp=string;
	while(*tmp!=s)
	{
			tmp++;
			if(*tmp=='\0')		//no end to tag flag an error
				return tmp;//will check against *tmp returning NULL would segfault
	}
	return tmp;
}




bool CScript::init(char* scr)
{
	char* tmp = scr;
	while(*tmp=='\n' || *tmp==' ' ||
	      *tmp=='\t' || *tmp==',')		//whitespace trim
	{
		tmp++;
		if(*tmp=='\0')		//whitespace went straight to eos
			return false;
	}
	if (*tmp!='<')	//if we didn't get a tag we got an argument save as arg and exit
	{
		children=NULL;
		value=scr;	//get rid of | | for strings (DO LATER)
		return true;
	}
	else		//otherwise we parse tag and all it's arguments(passing downwards)
	{
		children = new LinkedList<CScript>();
		tmp = safeGoto('>',tmp);
		if(*tmp=='\0')
			return false;
		char* buffer = new char[tmp-scr+2];
		memcpy(buffer,scr,tmp-scr+2);		
		buffer[tmp-scr+1]='\0';			
		value=buffer;				//tag should now be <something>
		//cerr << value << endl;
		//get beginning { skip whitespace and other stuff
		tmp = safeGoto('{',tmp);
		if(*tmp=='\0')
			return false;
		tmp++;			//go past {
		if(*tmp=='\0')		//nothing after { (segfault protection)
			return false;

		//start getting child arguments past '{' (if there are any)
		bool notDone=true;
		while(notDone)
		{
			while(*tmp=='\n' || *tmp==' ' ||
			      *tmp=='\t' || *tmp==',')		//whitespace trim
			{
				tmp++;
				if(*tmp=='\0')		//whitespace went straight to eos
					return false;
			}
			
			if (*tmp=='<')		//make a new recursing child
			{
				char* startPosition = tmp;
				tmp = safeGoto('>',tmp);
				if(*tmp=='\0')
					return false;
				tmp = safeGoto('{',tmp);				
				if(*tmp=='\0')	//never found { flag an error
					return false;
				tmp = cursePastBrackets(tmp);
				if(*tmp=='\0')
					return false;
				char* buffer=new char[tmp-startPosition+2];
				memcpy(buffer,startPosition,tmp-startPosition+2);
				buffer[tmp-startPosition+1]='\0';
				CScript *script = new CScript();
				children->insert(script);
				script->init(buffer);		//new script will span out here

			}//end of current child is recursive if block
			else	//if child wasn't recursive then it was just an argument
			{
				char* startPosition = tmp;
				//will catch empty tags here(ie <destroy> { }
				while(*tmp!='}' && *tmp!=',')
				{
					tmp++;
					if(*tmp=='\0')	//no end to argument flag error
						return false;
				}
				char* buffer=new char[tmp-startPosition+1];
				//no +1 because we don't want the } or ,
				memcpy(buffer,startPosition,tmp-startPosition+1);
				//but it does actually copy and the terminator doesn't so..
				buffer[tmp-startPosition]='\0';//terminate it
				CScript *script = new CScript();
				children->insert(script);		//add to list of children
				//std::cerr << "\t" << buffer << std::endl;
				script->init(buffer);		//script will store argument
				

			}//end of current child was non recursive handle block
			while(*tmp=='\n' || *tmp==' ' ||
			      *tmp=='\t' || *tmp==',')		//whitespace trim
			{
				tmp++;
				if(*tmp=='\0')		//whitespace went straight to eos
					return false;
			}
			if(*tmp=='}')			//found the end
				notDone=false;
		}//end of looping of argument parsing
		
		return true;
	}//end of main else block(handling a tag script)
	return false; //should never be hit
}


CScript* CScript::findChild(char* childTag,bool reset)
{
	if(children!=NULL)				//safety check
	{
		if(reset)
			children->beginning();
		do 
		{
			if((children->display())->value!=NULL)
			{
				if(strcmp((children->display())->value,childTag)==0)	//see if config's first undertag is includes
				{
						return children->display();
				}
			}
		}while(children->next());		//will drop through if nothing was found
	}
	return NULL;		//failed
}


/*
This code was originally in the Load function but on retrospect it probably should be somewhere else
and rewritten differently keep it around though cause it shows the format for using findChild

		children->beginning();
//test
		CScript *ptr = findChild("<includes>");	//find include block
		if(ptr!=NULL)
		{
			CScript *ptr = children->display();		//points to includes now
			ptr->children->beginning();
			CScript *ptrChild=NULL;
			char* includeFname;
			do
			{
				
				ptrChild = ptr->findChild("<include>");
				if(ptrChild!=NULL)
				{
					includeFname = (ptrChild->children->display())->value;
					cerr << "Found include file: " << includeFname
					     << endl;
					CScript *include = new CScript();
					if(include->Load(includeFname))
					{//if the load went through replace the filename with the actual script
						CScript *oldPtr = ptrChild->children->replace(include);
						delete oldPtr;	//prevent mem leak
					}
					else	//one of the scripts failed to load
					{
						cerr << "Scripts not loaded" << endl;
						return false;
					}
				}
				
				
			}while(ptrChild!=NULL && ptr->children->next());
		}


*/


