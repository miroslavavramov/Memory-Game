
#ifndef DECKOFCARDS_H_
#define DECKOFCARDS_H_
#include "Card.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <iterator>
using namespace std;
class DeckOfCards {
public:
	DeckOfCards();
	virtual ~DeckOfCards();
	void Init();
	void Shuffle();
    Card& getCard();

private:
	vector<Card> deck;
};

#endif /* DECKOFCARDS_H_ */
