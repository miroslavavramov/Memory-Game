/*
 * LButton.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: Todor
 */

#include "LButton.h"


LButton::LButton() {
	// TODO Auto-generated constructor stub
	m_X = 0;
	m_Y = 0;
	m_W = 0;
	m_H = 0;
	isIn = false;
}

//
void LButton::setPosition(int x, int y, int w, int h) {
	m_X = x;
	m_Y = y;
	m_W = w;
	m_H = h;
}

bool LButton::isInRect() {
	isIn = false;
	int xCoordinate, yCoordinate;
		SDL_GetMouseState( &xCoordinate, &yCoordinate );
		if(xCoordinate > m_X && xCoordinate < m_X + m_W && yCoordinate > m_Y && yCoordinate < m_Y + m_H )
			isIn = true;

		return isIn;
}
//
//void Button::handleEvent( SDL_Event* e )
//{
//	//If mouse event happened
//	if( e->type == SDL_MOUSEBUTTONDOWN  )
//	{
//		//Get
//		int x, y;
//		SDL_GetMouseState( &x, &y );
//
//		//Check if mouse is in button
//		bool inside = true;
//
//		//Mouse is left of the button
//		if( x < mPosition.x )
//		{
//			inside = false;
//		}
//		//Mouse is right of the button
//		else( x > mPosition.x + BUTTON_WIDTH )
//		{
//			inside = false;
//		}
//
//		//Mouse is inside button
//
//	}
//}
//
//void LButton::render()
//{
//	//Show current button sprite
//	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
//}
//
//LButton::~LButton() {
//	// TODO Auto-generated destructor stub
//}
//
