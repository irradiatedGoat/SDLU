#include "SDLutility.h"

int frame = 0;			// used for frame rate calculation
int lastFrame = 0;		// frame rate calc

double Delta_Time(void)
{
	CurTime   = SDL_GetTicks();
	DeltaTime = (CurTime - LastTime)/1000;
	LastTime  = CurTime;
	
	return DeltaTime;
};

SDL_Surface* SDLutility(char* windowName, int windowWidth, int windowHeight)
{
	
	/*
		Loads true type fonts for onscreen writeing
	*/
	if(TTF_Init()==-1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
	    exit(2);
	}
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption(windowName, windowName);
	return SDL_SetVideoMode(windowWidth, windowHeight, 0, 0);
};

void frameAdvance()
{
	frame++;
};
double frameRate()
{
	int tmp = SDL_GetTicks();
	// framerate = Number of frames/(delta Time/1000)
	double rate = double(frame/(double((tmp - lastFrame)/1000.0f)));
	// setup to calculate delta time again
	lastFrame = tmp;
	// reset frame count
	frame = 0;
	return rate;
};

char * intToStr(int value, char* str, int length)
{
	int temp = 10;
	int tempVal;
	
	for(int counter = 1; counter < length; counter++)
	{
		temp = temp*10;
	}
	tempVal = value - ((value/temp)*temp);
	int counter;
	for(counter = 0; counter < length; counter++)
	{
		
		temp = temp/10;
		int letter = tempVal/temp;
		str[counter] = (tempVal/temp)+48;
		tempVal = tempVal - (tempVal/temp)*10;
		if(counter == 0)
		{
			str[counter] = ' ';
		}
	}
	return str;
};
