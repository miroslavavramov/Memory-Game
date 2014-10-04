/*
 * BackgroundTexture.h
 *
 *  Created on: Sep 27, 2014
 *      Author: Todor
 */

#ifndef BACKGROUNDTEXTURE_H_
#define BACKGROUNDTEXTURE_H_
#include "SDL.h"
#include <SDL_image.h>
class BackgroundTexture {
public:
	BackgroundTexture();
	virtual ~BackgroundTexture();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);

private:
	SDL_Renderer* m_r;
	SDL_Texture* m_t;

};

#endif /* BACKGROUNDTEXTURE_H_ */
