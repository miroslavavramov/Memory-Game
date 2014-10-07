/*
 * Statistics.h
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "Card.h"
#include "Timer.h"
class Statistics {
public:
	Statistics();
	virtual ~Statistics();
	int bet = 5;
//	Card clickCount;
//	Timer currentTime;
	int calculateProfit();
	int getClickForLevel() const;
	void setClickForLevel(int clickForLevel);
	int getSecondToEnd() const;
	void setSecondToEnd(int secondToEnd);

private:
	int clickForLevel;
	int secondToEnd;
};

#endif /* STATISTICS_H_ */
