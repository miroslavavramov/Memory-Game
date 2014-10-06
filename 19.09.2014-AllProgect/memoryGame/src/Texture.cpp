/*
 * Texture.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: Todor
 */

#include "Texture.h"

//SDL_Renderer* gRenderer = NULL;
Texture::Texture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture() {
	//Deallocate
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* mR) {
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
		newTexture = SDL_CreateTextureFromSurface(mR, loadedSurface);
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

void Texture::free() {
	//Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void Texture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* mR) {
	//Set rendering space and render to screen
//	static int s = 0;
//	if(s== 40)
//		s=0;
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopy(mR, mTexture, clip, &renderQuad);
}

int Texture::getWidth() {
	return mWidth;
}

int Texture::getHeight() {
	return mHeight;
}