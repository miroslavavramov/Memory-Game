//============================================================================
// Name        : Bricks.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Ship.h"
#include "Ball.h"
#include "Brick.h"
using namespace std;

SDL_Window* m_pWindow;
SDL_Renderer* m_pRenderer;
SDL_Texture * BackGround;

int WIDTH = 800;
int HEIGHT = 600;

int main(int argc, char *args[]) {

	srand(time(0));
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_Color textColor = { 255, 255, 255 };
//	TTF_Font* font = TTF_OpenFont("C:/WINDOWS/Fonts/ARIAL.TTF", 30);
	m_pWindow = SDL_CreateWindow("___Bricks___  ", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	//Create Renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* Back = IMG_Load("images/image8a.jpg");

	//Create texture from surface pixels
	BackGround = SDL_CreateTextureFromSurface(m_pRenderer, Back);
	SDL_FreeSurface(Back);
	SDL_SetTextureBlendMode(BackGround, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(BackGround, 80);

	Ship sh;
	sh.Init(m_pRenderer);
//	Ball bl;
//	bl.Init(m_pRenderer);

vector<Brick> br;
Brick temp;
	int offset = 55;
	for (int i = 0; i < 12; i++) {
		temp.Init(m_pRenderer, offset, 50);
		br.push_back(temp);
		offset += 55;
	}


	bool gamerunning = true;
	SDL_Event event;

//	game loop
	while (gamerunning) {

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gamerunning = false;
		}


		sh.UpDate(event);
		SDL_RenderClear(m_pRenderer);

//		SDL_RenderCopy(m_pRenderer, BackGround, 0, 0);
		sh.Draw(m_pRenderer);

//		bl.Draw(m_pRenderer);



		for (int i = 0; i < br.size(); i++)
			br[i].Draw(m_pRenderer);



		SDL_RenderPresent(m_pRenderer);

	}

	return 0;
}

//bool checkColision(SDL_Rect r1, SDL_Rect r2) {
//	bool flagx = false;
//	bool flagy = false;
//	if (r1.x < r2.x) {
//		if ((r1.x + r1.w) > r2.x)
//			flagx = true;
//	} else {
//		if ((r2.x + r2.w) > r1.x)
//			flagx = true;
//	}
//	if (r1.y < r2.y) {
//		if ((r1.y + r1.w) > r2.y)
//			flagy = true;
//	} else {
//		if ((r2.y + r2.h) > r1.y)
//			flagy = true;
//	}
//	return (flagx & flagy);
//}
