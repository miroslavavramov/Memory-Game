/*
 * EventHandler.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Todor
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_
#include <SDL.h>


class EventHandler {
public:
	EventHandler();
	virtual ~EventHandler();
	void SetIvent(SDL_Event *);
private:
	SDL_Event event;
};

#endif /* EVENTHANDLER_H_ */
