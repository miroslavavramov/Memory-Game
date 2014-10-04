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
#include "StateManager.h"
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
	void Update(SDL_Event);
	int getState();

	private:
		SDL_Renderer* m_r;
		SDL_Texture* m_t;
		SDL_Texture* m_textTeam;
		SDL_Texture* m_textBackground[2];
};

#endif /* STARTBACKGROUNDTEXTURE_H_ */
