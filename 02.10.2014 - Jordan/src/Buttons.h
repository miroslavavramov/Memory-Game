#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;
class Buttons {
public:
	Buttons();
	virtual ~Buttons();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);

//	const SDL_Rect& getDestination() const;
	 void setDestination(int x_dest, int y_dest,int w_dest,int h_dest );
	 void setSource(int x_sourc, int y_sourc,int w_sourc,int h_sourc);
	 void ChangeCardState();
	 void Update(SDL_Event);
	 int getState() const;

private:
	 SDL_Renderer* m_r;
	 SDL_Texture* m_t;
	 SDL_Texture* m_textBullet;
	 SDL_Rect m_source;
	 SDL_Rect m_destination;
	 SDL_Rect m_sourceBullet;
	 SDL_Rect m_destinBullet;

	 int state;


};

#endif  BUTTONS_H_
