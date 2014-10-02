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
	void InitTeam(SDL_Renderer*);
	void InitRules(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void DrawTeam(SDL_Renderer*);
	void DrawRules(SDL_Renderer*);

	private:
		SDL_Renderer* m_r;
		SDL_Texture* m_t;
		SDL_Texture* m_textTeam;
};

#endif /* STARTBACKGROUNDTEXTURE_H_ */
