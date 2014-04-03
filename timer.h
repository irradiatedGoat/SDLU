#ifndef _SDLU_TIMER_H_
#define _SDLU_TIMER_H_
#include <SDL.h>

//////////////////////////////////////
//Timer.h
//	The timer is a wrapper class for the SDL timer.  Allows for starting,
//  stoping, reset, capping, and run checking.
//  
//////////////////////////////////////
class Timer
{
private:

	double	curTime,		//current SDL ticks
			deltaTime,		//the amount of time change from previous update
			maxTime,		//caps the values that deltaTime can return (see update for more on why)
			runningTime;	//the total ammount of time that the timer has been running (sum of deltas while timer is running)
	bool bRunning;			//true if the timer is running, false otherwise.
public:

	//See timer.cpp for detailed comments

	Timer();
	Timer(double maxDelta);	//default values with cap for delta
	void start();
	void stop();
	void reset();			//Sets everything but maxTime to 0
	double update();		//Needs to be called every cycle to keep pace with SDL timer

	// accessor functions.  
	bool isRunning()	{return bRunning;}
	double getRunTime()	{return runningTime;}
	double lastDelta()	{return deltaTime;}


};



static Timer systemTimer;


#endif