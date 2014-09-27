/*
 * Brick.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Todor
 */

#ifndef BRICK_H_
#define BRICK_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>

class Brick {
public:
	Brick();
	virtual ~Brick();
	void Init(SDL_Renderer*, int = 0, int = 0);
	void Draw(SDL_Renderer*);
private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect source;
	SDL_Rect destination;
};

#endif /* BRICK_H_ */
