


#ifndef CARD_H_
#define CARD_H_
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>
#include "SoundsBank.h"
using namespace std;
//SoundsBank* sound = NULL;

const int CARD_WIDTH = 79;
const int CARD_HEIGHT = 123;
class Card {
public:
	Card();
	virtual ~Card();
	int face;
	int suit;
	int state;

 void Init(SDL_Renderer*);
 void Draw(SDL_Renderer*);
 const SDL_Rect& getDestination() const;
 void setDestination(int x_dest, int y_dest);
 void Update(SDL_Event);
 void ChangeCardState();

 SDL_Renderer* m_r;
 SDL_Texture* m_t;
 SDL_Rect m_source;
 SDL_Rect m_destination;
 SoundsBank* sound = NULL;



};

#endif /* CARD_H_ */
