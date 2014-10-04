#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SoundsBank.h"
#include "Card.h"
using namespace std;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

enum stateButtons{
	HOVER_BUTTON = 1,
	NORMAL_BUTTON = 2,
	CLICK_BUTTON = 3,
};

class Buttons{
public:
	Buttons();
	virtual ~Buttons();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);

	 void setDestination(int x_dest, int y_dest,int w_dest,int h_dest );
	 void setSource(int x_sourc, int y_sourc,int w_sourc,int h_sourc);
	 void ChangeCardState();
	 void Update(SDL_Event);
	 void setState(stateButtons);
	 int getState() const;

private:
	 SDL_Renderer* m_r;
	 SDL_Texture* m_t;
	 SDL_Texture* m_textBullet;
	 SDL_Texture* m_textForTheTeam;
	 SDL_Rect m_source;
	 SDL_Rect m_destination;
	 SDL_Rect m_sourceBullet;
	 SDL_Rect m_destinBullet;
	 stateButtons m_currentStateButt;


};

#endif  BUTTONS_H_
