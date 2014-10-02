/*
 * StartBackgroundTexture.h
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#ifndef STARTBACKGROUNDTEXTURE_H_
#define STARTBACKGROUNDTEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>

class StartBackgroundTexture {
public:
	StartBackgroundTexture();
	virtual ~StartBackgroundTexture();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);

	private:
		SDL_Renderer* m_r;
		SDL_Texture* m_t;
};

#endif /* STARTBACKGROUNDTEXTURE_H_ */
