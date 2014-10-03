/*
 * Timer.cpp
 *
 *  Created on: 18.09.2014 ã.
 *      Author: Miroslav Avramov
 */

#include "Timer.h"

Timer::Timer() {
	//Initialize the variables
	    mStartTicks = 0;
	    mStarted = false;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start() {
	//Start the timer
	    mStarted = true;
	    //Get the current clock time
	    mStartTicks = SDL_GetTicks();
}


Uint32 Timer::getTicks() {
	//The actual timer time
		Uint32 time = 0;

	    //If the timer is running
	    if( mStarted )
	    {

	            //Return the current time minus the start time
	            time = SDL_GetTicks() - mStartTicks;

	    }

	    return time;
}

bool Timer::isStarted() {
	//Timer is running and paused or unpaused
	    return mStarted;
}
