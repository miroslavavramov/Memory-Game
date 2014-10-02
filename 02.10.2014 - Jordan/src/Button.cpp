/*
 * LButton.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: Todor
 */

#include "Button.h"

Button::Button() {
	// TODO Auto-generated constructor stub
	m_X = 0;
	m_Y = 0;
	m_W = 0;
	m_H = 0;
	isIn = false;
}

//
void Button::setPosition(int x, int y, int w, int h) {
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;
}

void Button::Init(SDL_Renderer* a)
{
	SDL_Surface* buttonSurface = IMG_Load("images/dots.png");
	if (!buttonSurface) {
		cerr << "images/dots.png: not found " << SDL_GetError() << endl;
	}
	m_t = SDL_CreateTextureFromSurface(a, buttonSurface);
	SDL_FreeSurface(buttonSurface);
}

void Button::Draw(SDL_Renderer* a)
{
	SDL_RenderCopy(a,m_t,&m_source[0],&m_destination);
}

void Button::Update(SDL_Event e)
{

}

bool Button::isInRect() {
	isIn = false;
	int xCoordinate, yCoordinate;
		SDL_GetMouseState( &xCoordinate, &yCoordinate );
		if(xCoordinate > m_X && xCoordinate < m_X + m_W && yCoordinate > m_Y && yCoordinate < m_Y + m_H )
			isIn = true;

		return isIn;
}
