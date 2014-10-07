/*
 * Statistics.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#include "Statistics.h"

Statistics::Statistics() {
	// TODO Auto-generated constructor stub

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

int Statistics::calculateProfit() {
	return 0;
//	bet*currentTime.GetSeconds();
}
