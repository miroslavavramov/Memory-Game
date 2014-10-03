/*
 * LButton.h
 *
 *  Created on: Sep 18, 2014
 *      Author: Todor
 */

#ifndef LBUTTON_H_
#define LBUTTON_H_
#include <SDL.h>
#include <SDL2/SDL.h>
//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y, int w, int h );
        bool isInRect();


	private:
		//Top left position
		int m_X;
		int m_Y;
		int m_W;
		int m_H;
		bool isIn;

};

#endif /* LBUTTON_H_ */
