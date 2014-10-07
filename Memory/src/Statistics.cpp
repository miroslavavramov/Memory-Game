
#include "Statistics.h"

Statistics::Statistics() {
	// TODO Auto-generated constructor stub
	credit = 50;
}

Statistics::~Statistics() {
	// TODO Auto-generated destructor stub
}

int Statistics::getSecondToEnd() const {
	return secondToEnd;
}

void Statistics::setSecondToEnd(int secondToEnd) {
	this->secondToEnd = secondToEnd;
}

void Statistics::setClickForLevel(int clickForLevel) {
	this->clickForLevel = clickForLevel;
}

int Statistics::getClickForLevel() const {
	return clickForLevel;
}

void Statistics::calculateProfit() {
    if(secondToEnd == 0){
    	profit = -5;
    }else{
    	profit =  ((bet * secondToEnd) - (((gameLevel + 2) * 2 ) - clickForLevel));
    }
    credit += profit;
}

//((gameLevel + 3) * 2) - clickForLevel;


void Statistics::setGameLevel(int gameLevel) {
	this->gameLevel = gameLevel;
}

int Statistics::getGameLevel() const {
	return gameLevel;
}

int Statistics::getProfit() const {
	return profit;
}

int Statistics::getCredit() const {
	return credit;
}

void Statistics::setCredit(int credit) {
	this->credit = credit;
}
