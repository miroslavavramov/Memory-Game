/*
 * Ball.h
 *
 *  Created on: Sep 22, 2014
 *      Author: Todor
 */

#ifndef BALL_H_
#define BALL_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>



class Ball {
private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect source;
	SDL_Rect destination;

public:
	Ball();
	//Ball(string);
	virtual ~Ball();
	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void UpDate(SDL_Event);

};

#endif /* BALL_H_ */
