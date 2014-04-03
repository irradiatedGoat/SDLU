#include "timer.h"

//////////
//  Constructor with all default values.  max deltaTime is 1000 ticks.
//  Timer defaults to not running.
//
//////////
Timer::Timer()
{
	curTime = 0;
	deltaTime = 0;
	maxTime = 1000;
	runningTime = 0;
	bRunning = false;
}


//////////
//  Constructor with all default values.  max deltaTime is 1000 ticks.
//  Timer defaults to not running.
//
//////////
Timer::Timer(double maxDelta)
{
	curTime = 0;
	deltaTime = 0;
	bRunning = true;
	maxTime = maxDelta;
	runningTime = 0;
}


//////////
// Start and stop the timer.
//
//////////
void Timer::start()
{
	curTime = SDL_GetTicks();
	deltaTime = 0;
	bRunning = true;
}
void Timer::stop()
{
	deltaTime = 0;
	bRunning = false;
}

//////////
//  Keep the timer on pace with the SDL timer, capped the maxTime.  Capping ensures
//  smooth animation regardless of PC lag.
//
//////////
double Timer::update()
{
	if(!bRunning)							// Time isn't advancing without this timer!
	{
		return 0;
	}

	double tempTime = SDL_GetTicks();		// Get the current SDL system time
	deltaTime = (tempTime - curTime)/1000;	// Calculate a new deltaTime
	curTime  = tempTime;					// Update the current time
	if(deltaTime > maxTime)					// Cap delta time
	{
		deltaTime = maxTime;
	}
	runningTime = runningTime + deltaTime;	// Add the delta to the total runtime of the timer.
	return deltaTime;
}

