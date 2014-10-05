#include "loader.h"
//for testing
using namespace std;
bool Loader::loadFonts(CScript *scr)
{
	if(scr==NULL)		//safety check
		return false;
	CScript* ptr;
	scr->children->beginning();	//reset to beginning of list
	do			//loop through rectgroups throwing error if one fails to load
	{
				
		ptr = scr->findChild("<font>");	//find next "<rectgroup>"
		if(ptr==NULL)
			return true;
		if(!loadFont(ptr))
			return false;
	}while(scr->children->next());
	return true;
}

bool Loader::loadFont(CScript *scr)
{
	scr->children->beginning();		//should be 100% safe now
	CScript *ptr = scr->findChild("<name>");
	if(ptr == NULL)
	{
		cout << "A font was not named!" << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	char* name = (ptr->children->display())->value;
	char *buff = new char[strlen(name)+1];	//don't reference the actual char* to preserve the reference table names even after deletion of the CScript
	//strcpy(buff,name);
	strcpy_s(buff, strlen(name)+1, name);
	buff[strlen(name)] = '\0';
	scr->children->beginning();
	ptr = scr->findChild("<pointsize>");
	if(ptr == NULL)
	{
		cout << "Point size not specificed for font" << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	int pointsize = atoi((ptr->children->display())->value);
	scr->children->beginning();
	ptr = scr->findChild("<file>");
	if(ptr == NULL)
	{
		cout << "Point size not specificed for font." << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	Font* f = new Font();
	f->init(ptr->children->display()->value,pointsize);
	fontSet.addReference(&buff[0],f);
	return true;
}

void displayScript(CScript* current)
{
	if(current == 0)
	{
		return;
	}
	cout<< "Error ";
	if(current->value != 0)
		cout<< current->value<< endl;
	if(current->children == 0)
	{
		return;
	}
	if(current->children->length() == 0)
	{
		return;
	}
	current->children->beginning();
	do{
		displayScript(current->children->display());
	}while(current->children->next());
}

//!loads script from file and populates all ReferenceTables
bool Loader::Load(char* file)
{
	if(!root->Load(file))		//failed to load script
		return false;

	root->children->beginning();
	//these will break if any of these functions fail to load
	if(!loadRectGroups(root->findChild("<rectgroups>")))
	{
		cout << "Error loading in rectgroups(check your script syntax)" << endl;
		return false;
	}
	root->children->beginning();
	if(!loadStateGroups(root->findChild("<stategroups>")))
	{
		cout << "Error loading in stategroups(check your script syntax)" << endl;
		return false;
	}

	root->children->beginning();
	if(!loadSprites(root->findChild("<sprites>")))
	{
		cout << "Error loading in sprites(check your script syntax)" << endl;
		return false;
	}

	root->children->beginning();
	if(!loadFonts(root->findChild("<fonts>")))
	{
		cout << "Error loading in Fonts(check you script syntax)" << endl;
		return false;
	}
	return true;
}

bool Loader::loadRectGroups(CScript *scr)
{
	if(scr==NULL)		//safety check
		return false;
	CScript* ptr;
	scr->children->beginning();	//reset to beginning of list
	do			//loop through rectgroups throwing error if one fails to load
	{
				
		ptr = scr->findChild("<rectgroup>");	//find next "<rectgroup>"
		if(ptr==NULL)
			return true;
		if(!loadRectGroup(ptr))
			return false;
	}while(scr->children->next());
	return true;
}

bool Loader::loadRectGroup(CScript *scr)
{
	CScript* ptr;
	//load in the name
	scr->children->beginning();
	ptr = scr->findChild("<name>");
	if(ptr==NULL)
		return false;
	if((ptr->children->display())->value==NULL)
		return false;
	char* name = (ptr->children->display())->value;
	char* buff = new char[strlen(name)+1];	//don't reference the actual char* to preserve the reference table names even after deletion of the CScript
	//strcpy(buff,name);
	strcpy_s(buff, strlen(name) + 1, name);
	buff[strlen(name)] = '\0';


	//start loading rects
	scr->children->beginning();
	int *size = new int;
	*size = scr->children->length()-1;
	SDL_Rect* buffRectGroup = new SDL_Rect[*size];
	int count = 0;
	do			//loop through rects throwing error if one fails to load
	{
				
		ptr = scr->findChild("<rect>");	//find next "<rectgroup>"
		if(ptr==NULL)
			return true;
		if(!loadRect(ptr,&buffRectGroup[count++]))
			return false;
	}while(scr->children->next());
	rectGroupSize.addReference(&buff[0],size);
	rectGroups.addReference(&buff[0], &buffRectGroup[0]);
	return true;
}

//rects contain an x,y,w,h
bool Loader::loadRect(CScript *scr, SDL_Rect* rect)
{
	//all of the null checking is to make sure that the script is correctly written
	//and to avoid a segfault in case it is
	scr->children->beginning();		//should be 100% safe now
	CScript *ptr = scr->findChild("<x>");
	if(ptr == NULL)
		return false;
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	rect->x = atoi((ptr->children->display())->value);

	scr->children->beginning();
	ptr = scr->findChild("<y>");
	if(ptr == NULL)
		return false;
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	rect->y = atoi((ptr->children->display())->value);

	scr->children->beginning();
	ptr = scr->findChild("<w>");
	if(ptr == NULL)
		return false;
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	rect->w = atoi((ptr->children->display())->value);

	scr->children->beginning();
	ptr = scr->findChild("<h>");
	if(ptr == NULL)
		return false;
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	rect->h = atoi((ptr->children->display())->value);
	return true;
}

bool Loader::loadStateGroups(CScript *scr)
{
	if(scr==NULL)	//safety check
		return false;
	CScript* ptr;
	scr->children->beginning();	//reset to beginning of list
	do			//loop through rectgroups throwing error if one fails to load
	{
				
		ptr = scr->findChild("<stategroup>");	//find next "<rectgroup>"
		if(ptr==NULL)
			return true;
		if(!loadStateGroup(ptr))
			return false;
	}while(scr->children->next());
	return true;
}

bool Loader::loadStateGroup(CScript *scr)
{
	CScript* ptr;
	//load in the name
	scr->children->beginning();
	ptr = scr->findChild("<name>");
	if(ptr==NULL)
		return false;
	if((ptr->children->display())->value==NULL)
		return false;

	char* name = (ptr->children->display())->value;
	char* buff = new char[strlen(name)+1];	//don't reference the actual char* to preserve the reference table names even after deletion of the CScript
	//strcpy(buff,name);
	strcpy_s(buff, strlen(name) + 1, name);
	buff[strlen(name)] = '\0';


	//start loading states
	scr->children->beginning();
	int *size = new int;
	*size = scr->children->length()-1;
	State* buffStateGroup = new State[*size];
	int count = 0;
	do			//loop through states throwing error if one fails to load
	{
				
		ptr = scr->findChild("<state>");	//find next "<rectgroup>"
		if(ptr==NULL)
			return true;
		//theoretically count should never exceed size so no check is required
		if(!loadState(ptr,&buffStateGroup[count++]))
		{
			cout << "Failed in loadState()" << endl;
			return false;
		}
	}while(scr->children->next());
	stateGroupSize.addReference(&buff[0],size);
	stateGroups.addReference(&buff[0], &buffStateGroup[0]);

	return true;
}

bool Loader::loadState(CScript *scr, State *state)
{
//char* bitmapName, SDL_Rect* frames, int numberOfFrames,Uint32 ColorKey
//Uint32 colorkey = SDL_MapRGB(screen->format, 128, 128, 128);
//strtol(const char *nptr, NULL,intbase)
	char* bmpName;
	Uint32 colorkey;
	unsigned long int la,lb,lc;//is needed for conversion sadly since there is no atoUint8
	Uint8 a,b,c;
	SDL_Rect* rectGroup;
	char* rectGroupName;
	int rectSize=0;
	//all of the null checking is to make sure that the script is correctly written
	//and to avoid a segfault in case it is
	scr->children->beginning();		//should be 100% safe now
	CScript *ptr = scr->findChild("<bitmap>");
	if(ptr == NULL)
	{
		cout << "NARG" << endl;
		return false;
	}
	if(ptr->children==NULL)
	{
		cout << "NARG" << endl;
		return false;
	}
	if((ptr->children->display())->value == NULL)
	{
		cout << "NARG" << endl;
		return false;
	}
	bmpName = (ptr->children->display())->value;

	scr->children->beginning();		//should be 100% safe now
	ptr = scr->findChild("<rectgroup>");
	if(ptr == NULL)
	{
		cout << "a state is missing a <rectgroup>"  << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	rectGroupName = (ptr->children->display())->value;
	rectGroup = rectGroups.lookup(rectGroupName);
	if(rectGroup==NULL)
	{
		cout << "Invalid Rectgroup in script:" << rectGroupName<<  endl;
		return false;
	}
	rectSize = *rectGroupSize.lookup(rectGroupName);	//assuming rectGroupSize has same entry as rectGroups so no error check
	scr->children->beginning();
	ptr = scr->findChild("<colorkey>");
	if(ptr == NULL)		//colorkey was not supplied using 0,0 pixel
	{
		if(state->init(bmpName, rectGroup, rectSize))
			return true;
		cout << "State Initialization failed (check your script)" << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	ptr->children->beginning();
	if(ptr->children->length()!=3)		//encounter more or less than three values for an RGB input
		return false;
	la = strtol(ptr->children->display()->value, NULL,0);
	a = unsigned(char(la));
	ptr->children->next();
	lb = strtol(ptr->children->display()->value, NULL,0);
	b = unsigned(char(lb));
	ptr->children->next();
	lc = strtol(ptr->children->display()->value, NULL,0);
	c = unsigned(char(lc));
	ptr->children->next();
	colorkey = SDL_MapRGB(screen->format, a, b, c);
	if(state->init(bmpName,rectGroup,rectSize,colorkey))
		return true;
	cout << "State Initialization failed (check your script)" << endl;
	return false;
}

bool Loader::loadSprites(CScript *scr)
{
	if(scr==NULL)	//safety check
	return false;
	CScript* ptr;
	scr->children->beginning();	//reset to beginning of list
	do			//loop through sprites
	{
				
		ptr = scr->findChild("<sprite>");
		if(ptr==NULL)
			return true;
		if(!loadSprite(ptr))
			return false;
	}while(scr->children->next());
	return true;
}

bool Loader::loadSprite(CScript *scr)
{
	Sprite* s = new Sprite;
	scr->children->beginning();		//should be 100% safe now
	CScript *ptr = scr->findChild("<name>");
	if(ptr == NULL)
	{
		cout << "Sprite was not named!" << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	char* name = (ptr->children->display())->value;
	char* buff = new char[strlen(name)+1];	//don't reference the actual char* to preserve the reference table names even after deletion of the CScript
	//strcpy(buff,name);
	strcpy_s(buff, strlen(name)+1, name);
	buff[strlen(name)] = '\0';

	scr->children->beginning();
	ptr = scr->findChild("<stategroup>");
	if(ptr == NULL)
	{
		cout << "Sprite has no stategroup!" << endl;
		return false;
	}
	if(ptr->children==NULL)
		return false;
	if((ptr->children->display())->value == NULL)
		return false;
	char *stateGroupName = ptr->children->display()->value;
	s->init(stateGroups.lookup(stateGroupName),*stateGroupSize.lookup(stateGroupName));
	sprites.addReference(stateGroupName,s);
	return true;
}
bool Loader::loadSpriteControllers(CScript *scr)
{
	return true;
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
