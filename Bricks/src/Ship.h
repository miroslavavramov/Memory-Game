/*
 * Ship.h
 *
 *  Created on: Sep 22, 2014
 *      Author: Todor
 */

#ifndef SHIP_H_
#define SHIP_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>


#include "EventHandler.h"

class Ship {
public:
	Ship();
	virtual ~Ship();
	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	const SDL_Rect& getDestination() const;
	void setDestination(const SDL_Rect& destination);
	void UpDate(SDL_Event);

private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect source;
	SDL_Rect destination;

	int acceleration;

};

#endif /* SHIP_H_ */
