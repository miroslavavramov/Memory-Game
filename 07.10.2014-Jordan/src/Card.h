


#ifndef CARD_H_
#define CARD_H_
#include "SDL.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SoundsBank.h"
using namespace std;
//SoundsBank* sound = NULL;

const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;

enum cardState{
	BACK_OF_CARD = 0,
	FACE_OF_CARD = 1,
	INVISIBLE_OF_CARD = 2,
};
class Card {
	 static int clickCount;
public:
	Card();
	virtual ~Card();
	int face;
	int suit;
	cardState m_currentStateOfCard;

 void Init(SDL_Renderer*);
 void Draw(SDL_Renderer*);
// const SDL_Rect& getDestination() const;
 void setDestination(int x_dest, int y_dest);
 void Update(SDL_Event);
 void ChangeCardState();

 SDL_Renderer* m_r;
 SDL_Texture* m_t;
 SDL_Rect m_source;
 SDL_Rect m_destination;




};

#endif /* CARD_H_ */
