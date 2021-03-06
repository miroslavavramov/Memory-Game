/*
 * Texture.h
 *
 *  Created on: Sep 18, 2014
 *      Author: Todor
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
class Texture {


	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile(std::string path, SDL_Renderer*);

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* = NULL);

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


#endif /* TEXTURE_H_ */
