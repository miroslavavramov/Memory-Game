//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include "DeckOfCards.h"
#include "Card.h"
#include "LButton.h"
using namespace std;

//Screen dimension constants
int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;
const int CARD_CANVAS_X = 150;
const int CARD_CANVAS_Y = 150;

// Set postion and size for sub window based on those of main window
int subSizeX = SCREEN_WIDTH / 2;
int subSizeY = SCREEN_HEIGHT / 2;

vector<Card> cardSet;
vector<int> cardStateChange;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* subRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[10];
SDL_Rect gSpriteButtonSound[2];
SDL_Rect gSpriteButtonSoundPosition[2];
SDL_Rect gSpriteButtonMenu[1];
//Texture gSpriteSheetTexture;
SDL_Texture* cardsTexture = NULL;
SDL_Texture* dotsTexture = NULL;
SDL_Texture* menuTexture = NULL;

//obekt za muzikata na igrata
Mix_Music *gScratchMusicGame = NULL;

//obekt za zvuka na Cartite
Mix_Chunk *gScratchButtonCard = NULL;
Mix_Chunk *gScratchRemoveCard = NULL;

//for remove borderer in subWindow, SDL_FALSE to remove border, SDL_TRUE to add borde
SDL_bool bordered = SDL_FALSE;

SDL_DisplayMode current;

int main(int argc, char* args[]) {
	int fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;

	//zarejdame zvucite
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

	//SDL init video
	if (SDL_Init( SDL_INIT_EVERYTHING) < 0)
	{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	//Create window
	gWindow = SDL_CreateWindow("MemoryCards", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1,SDL_RENDERER_ACCELERATED);

	//Load Media From file
//	gSpriteSheetTexture.loadFromFile("images/cards.png", gRenderer);

	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load("images/cards.png");

	//Create texture from surface pixels
	cardsTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	//Load image from specified path
	loadedSurface = IMG_Load("images/dots.png");

	//Create texture from surface pixels
	dotsTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	loadedSurface = IMG_Load("images/button-menu.png");
	menuTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
	SDL_FreeSurface(loadedSurface);
	//set ICON of Window
	loadedSurface = IMG_Load("images/icon.png");
	SDL_SetWindowIcon(gWindow,loadedSurface);
	SDL_FreeSurface(loadedSurface);

	//Load sound effects
	gScratchButtonCard = Mix_LoadWAV( "sounds/button-24.wav");
	gScratchRemoveCard = Mix_LoadWAV("sounds/poznati-iz4ezvat-karti.wav");
	gScratchMusicGame=Mix_LoadMUS("sounds/cautious-path-01.mp3");

	//Play Music Game
	if(gScratchMusicGame)
	{
		Mix_PlayMusic(gScratchMusicGame,1);
	}

	// Create cards and shuffle
	DeckOfCards newDeck;
	newDeck.Init();
	newDeck.Shuffle();
	Card temp;

	for (int iter = 0; iter < 4; iter++) {

		temp = newDeck.getCard();
		cardSet.push_back(temp);
		cardSet.push_back(temp);

	}
	srand(time(NULL));
	random_shuffle(cardSet.begin(), cardSet.end());

	//Set top left sprite
	for (int iter = 0; iter < 8; iter++)
	{
		gSpriteClips[iter].x = CARD_WIDTH * cardSet[iter].face;
		gSpriteClips[iter].y = CARD_HEIGHT * cardSet[iter].suit;
		gSpriteClips[iter].w = CARD_WIDTH;
		gSpriteClips[iter].h = CARD_HEIGHT;
	}

	//	card back
		gSpriteClips[8].x = CARD_WIDTH * 2;
		gSpriteClips[8].y = CARD_HEIGHT * 4;
		gSpriteClips[8].w = CARD_WIDTH;
		gSpriteClips[8].h = CARD_HEIGHT;

	//	card no draw
		gSpriteClips[9].x = 0;
		gSpriteClips[9].y = 0;
		gSpriteClips[9].w = 0;
		gSpriteClips[9].h = 0;

	//button SoundMute
	//Koq 4ast ot kartinkata da vzemem  - destination rectangle
	gSpriteButtonSound[0].x = 0;
	gSpriteButtonSound[0].y = 0;
	gSpriteButtonSound[0].w = 50;
	gSpriteButtonSound[0].h = 50;

	gSpriteButtonSound[1].x = 50;
	gSpriteButtonSound[1].y = 0;
	gSpriteButtonSound[1].w = 50;
	gSpriteButtonSound[1].h = 50;

	gSpriteButtonMenu[0].x = 0;
	gSpriteButtonMenu[0].y = 0;
	gSpriteButtonMenu[0].w = 50;
	gSpriteButtonMenu[0].h = 50;

	//Kyde da izobrazim tazi 4ast ot kartinkata - na kakva poziciq   - source rectangle
	gSpriteButtonSoundPosition[0].x = 0;
	gSpriteButtonSoundPosition[0].y = 100;
	gSpriteButtonSoundPosition[0].w = 50;
	gSpriteButtonSoundPosition[0].h = 50;

	gSpriteButtonSoundPosition[1].x = SCREEN_WIDTH - gSpriteButtonSound[1].w;
	gSpriteButtonSoundPosition[1].y = 0;
	gSpriteButtonSoundPosition[1].w = 50;
	gSpriteButtonSoundPosition[1].h = 50;

			bool quit = false;
           int soundButton = 0;
			//Event handler
			SDL_Event e;
			LButton button;
			SDL_Rect cardPosition;
			//While application is running
			while (!quit)
			{

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{


					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					} else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_RETURN:
//

//								fullscreen = !fullscreen;
							if (fullscreen == SDL_WINDOW_FULLSCREEN_DESKTOP)
							{
								fullscreen = 0;
								SCREEN_WIDTH = 640;
								gSpriteButtonSoundPosition[1].x = SCREEN_WIDTH - gSpriteButtonSound[1].w;
								gSpriteButtonSoundPosition[1].y = 0;
								gSpriteButtonSoundPosition[1].w = 50;
								gSpriteButtonSoundPosition[1].h = 50;
							}

							else
							{
								fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;

								//Този цикъл взима размера на текъщия Display Mode
								for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
								{

								    SDL_GetCurrentDisplayMode(i, &current);
								    SCREEN_WIDTH = current.w;
								    	gSpriteButtonSoundPosition[1].x = SCREEN_WIDTH - gSpriteButtonSound[1].w;
								    	gSpriteButtonSoundPosition[1].y = 0 * 150;
								    	gSpriteButtonSoundPosition[1].w = 50;
								    	gSpriteButtonSoundPosition[1].h = 50;
								}
							}

							if (SDL_SetWindowFullscreen(gWindow, fullscreen)!= 0)
							{
								printf("Unable to switch window to fullscreen mode:  %s\n",SDL_GetError());
								SDL_ClearError();

							}
							break;
						}
					}


					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{

						int i = 0;
						for (int yC = CARD_CANVAS_Y; yC <= 290; yC += 140)
						{
							for (int xC = CARD_CANVAS_X; xC <= 450; xC += 100)
							{
								button.setPosition(xC, yC, CARD_WIDTH,CARD_HEIGHT);
								if (button.isInRect())
								{
//*******************
									if (cardSet[i].state == 0)
									{
										cardSet[i].state = 1;
										if (cardStateChange.size() == 0)
										{
											cardStateChange.push_back(i);

										}
										else if (cardStateChange.size() == 1)
										{
											cardStateChange.push_back(i);

											if (cardSet[cardStateChange[0]].face
													== cardSet[cardStateChange[1]].face
													&& cardSet[cardStateChange[0]].suit
															== cardSet[cardStateChange[1]].suit)
											{
												cardSet[cardStateChange[0]].state = 2;
												cardSet[cardStateChange[1]].state = 2;
												cardStateChange.clear();
												//playvame zvuka
												Mix_PlayChannel( -1, gScratchRemoveCard, 0 );
											}

										}
										else if (cardStateChange.size() == 2)
										{
											cardStateChange.push_back(i);
											cardSet[cardStateChange[0]].state = 0;
											cardSet[cardStateChange[1]].state = 0;
											cardStateChange[0] = cardStateChange[2];
											cardStateChange.pop_back();
											cardStateChange.pop_back();
										}
		//

									} //end else if



//**********************
									//playvame zvuka
									Mix_PlayChannel( -1, gScratchButtonCard, 0 );
								}
								i++;
							}

						}

						button.setPosition(0,0,50,50);
						if(button.isInRect())
						{
							SDL_Window* subWindow  = SDL_CreateWindow( "Menu" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, subSizeX, subSizeY, 0 );
							subRenderer  = SDL_CreateRenderer( subWindow, -1, SDL_RENDERER_ACCELERATED );
							SDL_SetWindowBordered(subWindow,bordered);
							SDL_SetRenderDrawColor( subRenderer , 0, 255, 0, 255 );
							SDL_RenderClear(subRenderer);

						}

						button.setPosition(SCREEN_WIDTH - gSpriteButtonSound[1].w,1,45,48);
						if (button.isInRect())
						{
							if(soundButton == 1)
							{
								soundButton = 0;
								if(Mix_PlayingMusic() == 1)
								{
									Mix_ResumeMusic();
								}
							}
							else
							{
								soundButton = 1;
								if(Mix_PlayingMusic() == 1)
								{
									Mix_PauseMusic();
								}

								soundButton = 1;
							}


						}

					}
				}



				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x01, 0xBF, 0xFF);
				SDL_RenderClear(gRenderer);
				int i = 0;
				for (int yC = CARD_CANVAS_X; yC <= 290; yC += 140)
				{
					for (int xC = CARD_CANVAS_X; xC <= 450; xC += 100)
					{
						cardPosition.x = xC;
						cardPosition.y = yC;
						cardPosition.w = CARD_WIDTH;
						cardPosition.h = CARD_HEIGHT;

					if (cardSet[i].state == 1)
					{
						SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[i],&cardPosition);

					}

					else if(cardSet[i].state == 0)
					{
						SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[8],&cardPosition);
					}

					else
					{
						SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[9],&cardPosition);
					}



						i++;
					}
				}
						SDL_RenderCopy(gRenderer,menuTexture,&gSpriteButtonMenu[0],&gSpriteButtonMenu[0]);
						SDL_RenderCopy(gRenderer,dotsTexture,&gSpriteButtonSound[soundButton], &gSpriteButtonSoundPosition[1]);
						SDL_RenderPresent(subRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_Delay(50);
			}

	return 0;
}
