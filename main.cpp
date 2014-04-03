#include <iostream>
#include <SDL.h>
#include <math.h>
#include <vector>
#include "SDLutility.h"
#include "VoiceGui.h"

int main(int argc, char* argv[])
{
	
	//SDL setup
	SDL_Surface *screen = SDLutility("Speech Recognition", SCREEN_WIDTH, SCREEN_HEIGHT);
  	
	//keyboard/mouse input
	SDL_Event event;
	KeyHandler handler;

	//in game graphics system setup
	Window mainWindow(screen);					//drawing

	Registry appReg(&mainWindow, &handler);	//sprite management and destruction
	

	
	systemTimer.start();
	//flow control variables
	int quitMainLoop = 0;

	// message pump 
	while(!quitMainLoop)
	{
		// look for an event
    	if (SDL_PollEvent(&event))
		{// an event was found
			
			handler.processM(event);		//give the event to the key handler to be processed
			if(event.type == SDL_QUIT)
    			quitMainLoop = 1;			// catch the window being closed
			
    	}
		//escape key hit... pause game
		if(handler.keys[SDLK_ESCAPE].switched)
		{
			//example code
		}
		// f hit ... display framerate....and total running time
		if(handler.keys[SDLK_f].switched)
		{

			handler.keys[SDLK_f].switched = false;
			std::cout << "FR:" << frameRate() << "\t Timer tally:" << systemTimer.getRunTime() << std::endl;
		}
		if (handler.keys[SDLK_y].switched)
		{
			handler.keys[SDLK_y].switched = false;
			std::cout << mainWindow.length()<< std::endl;
		}
		


			//gameKeyInput(handler, gameReg, loader);
			//gameCode(handler, gameReg, gameLoader, loader, gameCL, systemTimer);
			//gameLoader.updateWindow(gameReg, systemTimer);
			mainWindow.ZOrderSort();
			mainWindow.update(systemTimer.update());
			mainWindow.draw();

		
		


		// actuall hard draw to the screen
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		
		// for framerate calculation
		frameAdvance();
		
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}
