/*
 * Timer.h
 *
 *  Created on: 18.09.2014 ã.
 *      Author: Miroslav Avramov
 */

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>


#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
	Timer();
	virtual ~Timer();
	//The various clock actions
	void start();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The timer status
	bool mStarted;
};

#endif /* TIMER_H_ */
