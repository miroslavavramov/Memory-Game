
#include "DeckOfCards.h"

DeckOfCards::DeckOfCards() {
	// TODO Auto-generated constructor stub

}

DeckOfCards::~DeckOfCards() {
	// TODO Auto-generated destructor stub
}

void DeckOfCards::Init() {

	Card card;

	for(int i = 0; i < 52; ++i){
		card.face = i % 13;
		card.suit = i / 13;
		card.m_currentStateOfCard = FACE_OF_CARD;
        deck.push_back(card);
	}
}

void DeckOfCards::Shuffle() {
	srand(time(NULL));
	random_shuffle ( deck.begin(), deck.end() );
}

Card& DeckOfCards::getCard() {
	Card   temp;
	if(deck.size() < 1){
		this-> Init();
		this -> Shuffle();
	}
	temp = deck.back();
	deck.pop_back();
return temp;

}
