/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include "DeckOfCards.h"
#include "Card.h"
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;
const int CARD_CANVAS_X = 150;
const int CARD_CANVAS_Y = 150;

#define FULLSCREEN = 0;
//Texture wrapper class
class LTexture {
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[8];
LTexture gSpriteSheetTexture;

LTexture::LTexture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
		IMG_GetError());
	} else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
				SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n",
					path.c_str(), SDL_GetError());
		} else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	//Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("MemoryCards", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1,
					SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				success = false;
			} else {

				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf(
							"SDL_image could not initialize! SDL_mage Error: %s\n",
							IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag

	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("images/cards.png")) {
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	} else {
		DeckOfCards newDeck;
		newDeck.Init();
		newDeck.Shuffle();
		Card temp;
		vector<Card> cardSet;

		for (int iter = 0; iter < 4; iter++) {

			temp = newDeck.getCard();
			cardSet.push_back(temp);
			cardSet.push_back(temp);

		}
		srand(time(NULL));
		random_shuffle(cardSet.begin(), cardSet.end());
		srand(time(NULL));
		random_shuffle(cardSet.begin(), cardSet.end());

		//Set top left sprite
		for (int iter = 0; iter < 8; iter++) {

			gSpriteClips[iter].x = CARD_WIDTH * cardSet[iter].face;
			gSpriteClips[iter].y = CARD_HEIGHT * cardSet[iter].suit;
			gSpriteClips[iter].w = CARD_WIDTH;
			gSpriteClips[iter].h = CARD_HEIGHT;
		}

	}

	return success;
}

void close() {
	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[]) {

	int fullscreen = 4097;

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit) {
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if (e.type == SDL_QUIT){
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_ESCAPE:
								quit = true;
							break;

//							case SDLK_RETURN:
//								SDL_SetWindowFullscreen(gWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
//								break;
							case SDLK_RETURN:
//
//								fullscreen = !fullscreen;

							if (fullscreen == 4097)
							{
								fullscreen = 0;
							}

							else
							{
								fullscreen = 4097;
							}

							 if (SDL_SetWindowFullscreen(gWindow,fullscreen) != 0) {
							printf ("Unable to switch window to fullscreen mode:  %s\n", SDL_GetError());
							SDL_ClearError();

					    }
							break;
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render top left sprite
				gSpriteSheetTexture.render(150, 150, &gSpriteClips[0]);
				gSpriteSheetTexture.render(250, 150, &gSpriteClips[1]);
				gSpriteSheetTexture.render(350, 150, &gSpriteClips[2]);
				gSpriteSheetTexture.render(450, 150, &gSpriteClips[3]);
//				**********************
				gSpriteSheetTexture.render(150, 290, &gSpriteClips[4]);
				gSpriteSheetTexture.render(250, 290, &gSpriteClips[5]);
				gSpriteSheetTexture.render(350, 290, &gSpriteClips[6]);
				gSpriteSheetTexture.render(450, 290, &gSpriteClips[7]);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
