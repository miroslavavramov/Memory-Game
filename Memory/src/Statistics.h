

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "Card.h"
#include "Timer.h"
class Statistics {
public:
	Statistics();
	virtual ~Statistics();


	void calculateProfit();
	int getClickForLevel() const;
	void setClickForLevel(int clickForLevel);
	int getSecondToEnd() const;
	void setSecondToEnd(int secondToEnd);
	void setGameLevel(int gameLevel);
	int getGameLevel() const;
	int getProfit() const;
	int getCredit() const;
	void setCredit(int credit);

private:

	int credit;
	int bet = 5;
	int profit;

	int clickForLevel;
	int secondToEnd;
	int gameLevel;
};

#endif /* STATISTICS_H_ */
