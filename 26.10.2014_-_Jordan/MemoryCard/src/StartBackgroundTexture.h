/*
 * StartBackgroundTexture.h
 *
 *  Created on: Sep 30, 2014
 *      Author: User
 */

#ifndef STARTBACKGROUNDTEXTURE_H_
#define STARTBACKGROUNDTEXTURE_H_

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "StateManager.h"
#include "Statistics.h"
#include "Text.h"

class StartBackgroundTexture {
public:
	StartBackgroundTexture();
	virtual ~StartBackgroundTexture();

	void Init(SDL_Renderer*);
	void InitRules(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void DrawRules(SDL_Renderer*);
	void Update(SDL_Event e);
	void InitSatistics(SDL_Renderer*);
	void DrawSatistics(SDL_Renderer*);

private:
	Text m_txtStatistics;
	Statistics m_statRecord;
	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Texture* m_textBackground;

	SDL_Texture* m_textRules;
	SDL_Texture* m_textStat;

};

#endif /* STARTBACKGROUNDTEXTURE_H_ */
