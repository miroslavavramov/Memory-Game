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
const int CARD_WIDTH_DEST = 79;
const int CARD_HEIGHT_DEST = 123;
enum cardState {
	BACK_OF_CARD = 0, FACE_OF_CARD = 1, INVISIBLE_OF_CARD = 2,
};
class Card {

public:
	static int clickCount;
	Card();
	virtual ~Card();

	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void setDestination(int x_dest, int y_dest);
	void Update(SDL_Event);
	void ChangeCardState();
	int getClickCount() const;
	void setClickCount(int clickCount);

	SDL_Renderer* m_r;
	SDL_Texture* m_t;
	SDL_Rect m_source;
	SDL_Rect m_destination;

	cardState m_currentStateOfCard;
	cardState m_NewStateOfCard;

	unsigned int face;
	unsigned int suit;
	unsigned int m_lastTime;
	unsigned int m_currentTime;
	int m_speed;

};

#endif /* CARD_H_ */
