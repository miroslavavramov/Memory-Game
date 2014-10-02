// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Text.h"
using namespace std;

SDL_Window* g_pWindow;
SDL_Renderer* g_pRenderer;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

	//initialize SDL_ttf
	if (TTF_Init() == -1) {
		cerr << "TTF_Init: " << TTF_GetError() << endl;
//exit(2);
	}

	SDL_Texture* backGroundTexture; // the new SDL_Texture variable
	SDL_Texture* backimageTexture;
// *****************



	SDL_Init( SDL_INIT_EVERYTHING);

	//Create window
	g_pWindow = SDL_CreateWindow("Easy_Rider", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create Renderer
	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);

	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load("image/background.png");

	//Create texture from surface pixels
	backGroundTexture = SDL_CreateTextureFromSurface(g_pRenderer,
			loadedSurface);

	SDL_Surface* riderSurface = SDL_LoadBMP("image/rider.bmp");

	//Color key image
	SDL_SetColorKey(riderSurface, SDL_TRUE,
			SDL_MapRGB(riderSurface->format, 102, 204, 255));

	//Create texture from surface pixels
	backimageTexture = SDL_CreateTextureFromSurface(g_pRenderer, riderSurface);

	//SDL_Rect rectRider = {320, 0, riderSurface->w};

// flipping a image
	Text txt;
	txt.Init(g_pRenderer);

	SDL_RenderClear(g_pRenderer);


	bool gamerunning = true;
	SDL_Event event;

	//	game loop
	while (gamerunning) {

		if (SDL_PollEvent(&event)!= 0) {
			if (event.type == SDL_QUIT)
				gamerunning = false;
		}
			SDL_RenderClear(g_pRenderer);
					SDL_RenderCopy(g_pRenderer, backGroundTexture, 0, 0);
					txt.Draw(g_pRenderer);
			        txt.UpDate(event);
					SDL_RenderPresent(g_pRenderer);



	}

	SDL_RenderPresent(g_pRenderer);

	//SDL_Delay(2000);

	return 0;
}
