/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include "DeckOfCards.h"
#include "Card.h"
//#include "Texture.h"
#include "LButton.h"
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;
const int CARD_CANVAS_X = 150;
const int CARD_CANVAS_Y = 150;

//#define FULLSCREEN = 0;
vector<Card> cardSet;
vector<int> cardStateChange;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[10];
//Texture gSpriteSheetTexture;
SDL_Texture* cardsTexture = NULL;
SDL_Texture* dotsTexture = NULL;

int main(int argc, char* args[]) {

	int fullscreen = 4097;

	//SDL init video
	if (SDL_Init( SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//			success = false;
	}

	//Create window
	gWindow = SDL_CreateWindow("MemoryCards", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

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
	for (int iter = 0; iter < 8; iter++) {
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
//	//Start up SDL and create window

	bool quit = false;

	//Event handler
	SDL_Event e;
	LButton button;
	SDL_Rect cardPosition;
	//While application is running
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;

//							case SDLK_RETURN:
//								SDL_SetWindowFullscreen(gWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
//								break;
				case SDLK_RETURN:
//
//

					if (fullscreen == 4097) {
						fullscreen = 0;
					}

					else {
						fullscreen = 4097;
					}

					if (SDL_SetWindowFullscreen(gWindow, fullscreen) != 0) {
						printf(
								"Unable to switch window to fullscreen mode:  %s\n",
								SDL_GetError());
						SDL_ClearError();

					}
					break;
				}
			}

			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int i = 0;
				for (int yC = 150; yC <= 290; yC += 140) {
					for (int xC = 150; xC <= 450; xC += 100) {
						button.setPosition(xC, yC, CARD_WIDTH, CARD_HEIGHT);
						if (button.isInRect()) {
							if (cardSet[i].state == 0) {
								cardSet[i].state = 1;
								if (cardStateChange.size() == 0) {
									cardStateChange.push_back(i);

								} else if (cardStateChange.size() == 1) {
									cardStateChange.push_back(i);

									if (cardSet[cardStateChange[0]].face
											== cardSet[cardStateChange[1]].face
											&& cardSet[cardStateChange[0]].suit
													== cardSet[cardStateChange[1]].suit) {
//										cout << cardSet[cardStateChange[0]].face<<" "<<
//												cardSet[cardStateChange[1]].face<<" "<<
//											 cardSet[cardStateChange[0]].suit<<" "<<
//												cardSet[cardStateChange[1]].suit<< endl;

										cardSet[cardStateChange[0]].state = 2;
										cardSet[cardStateChange[1]].state = 2;
										cardStateChange.clear();
									} else {
										cardSet[cardStateChange[0]].state = 0;
										cardSet[cardStateChange[1]].state = 0;

									}

								} else if (cardStateChange.size() == 2) {
									cardStateChange.push_back(i);
//									cardSet[cardStateChange[0]].state = 0;
//									cardSet[cardStateChange[1]].state = 0;
//									 myvector.front() -= myvector.back();
									cardStateChange[0] = cardStateChange[2];
									cardStateChange.pop_back();
									cardStateChange.pop_back();
								}
//

							} //end else if
//							cout << "Card face " << cardSet[i].face << " suit "
//									<< cardSet[i].suit << " is clicked! "
//									<< cardSet[i].state << " is state! "
//									<< endl;

						}
						i++;
					}

				}

			}

		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);
		int i = 0;
		for (int yC = 150; yC <= 290; yC += 140) {
			for (int xC = 150; xC <= 450; xC += 100) {
				cardPosition.x = xC;
				cardPosition.y = yC;
				cardPosition.w = CARD_WIDTH;
				cardPosition.h = CARD_HEIGHT;
				if (cardSet[i].state == 1) {
					SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[i],
							&cardPosition);
				} else if (cardSet[i].state == 0) {
					SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[8],
							&cardPosition);
				} else {
					SDL_RenderCopy(gRenderer, cardsTexture, &gSpriteClips[9],
							&cardPosition);
				}

				i++;
			}
		}
		SDL_RenderCopy(gRenderer, dotsTexture, NULL, NULL);

//Update screen
		SDL_RenderPresent(gRenderer);
		SDL_Delay(50);
	}
//		}
//	}

//Free resources and close SDL
//	close();

	return 0;
}
