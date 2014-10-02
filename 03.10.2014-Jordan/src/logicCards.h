#ifndef LOGICCARDS_H_
#define LOGICCARDS_H_

#include "DeckOfCards.h"
#include "Card.h"
#include <vector>
#include <ctime>
#include <set>
#include "SoundsBank.h"
class logicCards {
public:
	logicCards();
	void Init(SDL_Renderer*);
	void Draw(SDL_Renderer*);
	void Update(SDL_Event);
	void GetCardFromDeck();
	void compareCard();
	virtual ~logicCards();

//private:
	SDL_Renderer* m_pRenderer;
	vector<Card> m_cardSet;
	set<int> m_TwoCard;
	set<int>::iterator m_Begin;
	set<int>::iterator m_End;
	DeckOfCards m_newDeck;
	Card m_Cards;
};

#endif /* LOGICCARDS_H_ */
