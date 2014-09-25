#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 480;
const int CARD_ANIMATION_frame = 4;
const int CARD_SUIT_ANIMATION = 5;
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene
SDL_Rect gameCard[CARD_ANIMATION_frame];
SDL_Rect gameCardPos;
SDL_Rect gameCardSuit[CARD_SUIT_ANIMATION];
SDL_Rect gameCardSuitPos;
//Texture
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* gameCardTexture = NULL;
SDL_Texture* gameCardSuitTexture = NULL;


int main(int argc, char* args[]) {

	if (SDL_Init( SDL_INIT_EVERYTHING) < 0)
	{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	//Create window
	gWindow = SDL_CreateWindow("Task 01", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1,SDL_RENDERER_ACCELERATED);

	SDL_Surface* loadedSurface = IMG_Load("images/background.png");
	backgroundTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
	SDL_FreeSurface(loadedSurface);

	loadedSurface = IMG_Load("images/cards.png");
//	SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xFF,0xFF,0xFF));
	gameCardTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
	SDL_FreeSurface(loadedSurface);

	loadedSurface = IMG_Load("images/suit.png");
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xff, 0xff, 0xff ) );
	gameCardSuitTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
	SDL_FreeSurface(loadedSurface);


	gameCard[0].x = 0;
	gameCard[0].y = 0;
	gameCard[0].w = 79;
	gameCard[0].h = 123;

	gameCard[1].x = 80;
	gameCard[1].y = 0;
	gameCard[1].w = 79;
	gameCard[1].h = 123;

	gameCard[2].x = 790;
	gameCard[2].y = 246;
	gameCard[2].w = 79;
	gameCard[2].h = 123;

	gameCard[3].x = 158;
	gameCard[3].y = 0;
	gameCard[3].w = 79;
	gameCard[3].h = 123;


	gameCardPos.x = 0;
	gameCardPos.y = 0;
	gameCardPos.w = 79;
	gameCardPos.h = 123;

	gameCardSuit[0].x = 0;
	gameCardSuit[0].y = 0;
	gameCardSuit[0].w = 90;
	gameCardSuit[0].h = 100;

	gameCardSuit[1].x = 90;
	gameCardSuit[1].y = 0;
	gameCardSuit[1].w = 100;
	gameCardSuit[1].h = 100;

	gameCardSuit[2].x = 190;
	gameCardSuit[2].y = 0;
	gameCardSuit[2].w = 100;
	gameCardSuit[2].h = 100;
//
	gameCardSuit[3].x = 290;
	gameCardSuit[3].y = 0;
	gameCardSuit[3].w = 100;
	gameCardSuit[3].h = 100;


	gameCardSuitPos.x = 100;
	gameCardSuitPos.y = 100;
	gameCardSuitPos.w = 100;
	gameCardSuitPos.h = 100;






				//Main loop flag
				bool quit = false;

				SDL_Event e;

				int frameCard = 0;
				int frameSuit = 0;
				//While application is running
				while( !quit )
				{


					//Handle events on queue
					while( SDL_PollEvent( &e ) != 0 )
					{
						//User requests quit
						if( e.type == SDL_QUIT )
						{
							quit = true;
						}

					}

					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x01, 0xBF, 0xFF);
					SDL_RenderClear(gRenderer);
//					SDL_RenderCopy(gRenderer,backgroundTexture,NULL,NULL);


					frameCard = (SDL_GetTicks() / 500) % 4;
					frameSuit = (SDL_GetTicks() / 500) % 4;

					++frameCard;
					++frameSuit;


					//Cycle animation
					if( frameCard / 4 >= CARD_ANIMATION_frame )
					{
						frameCard = 0;
					}

					//Cycle animation
					if( frameSuit / 4 >= CARD_SUIT_ANIMATION )
					{
						frameSuit = 0;
					}

					SDL_RenderCopy(gRenderer,gameCardTexture,&gameCard[frameCard],&gameCardPos);
					SDL_RenderCopy(gRenderer,gameCardSuitTexture,&gameCardSuit[frameSuit],&gameCardSuitPos);
//					SDL_RenderCopy(gRenderer,gameCardSuitTexture,&gameCardSuit[0],&gameCardSuitPos);

					//Update screen
					SDL_RenderPresent( gRenderer );

				}


	SDL_RenderPresent(gRenderer);
	return 0;
}
