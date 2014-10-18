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
//	void animateCard();
	virtual ~logicCards();

	int getCountInvCards() const {
		return m_CountInvCards;
	}
	int getTempLevel() const {
		return TempLevel;
	}

	const vector<Card>& getCardSet() const {
		return m_cardSet;
	}

	void setCardSet(const vector<Card>& cardSet) {
		m_cardSet = cardSet;
	}

	set<int> m_TwoCard;

private:
	vector<Card> m_cardSet;
	SDL_Renderer* m_pRenderer;
	set<int>::iterator m_Begin;
	set<int>::iterator m_End;
	DeckOfCards m_newDeck;
	Card m_Cards;
//	dont forget to replace
	int TempLevel;
	int m_CountInvCards;
	int CardSetX;
	int CardSetY;
	int CardSetOffsetX;
	int CardSetOffsetY;

	unsigned int m_lastTime;
	unsigned int m_currentTime;
};

#endif /* LOGICCARDS_H_ */
