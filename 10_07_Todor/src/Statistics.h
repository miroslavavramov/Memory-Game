

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "Card.h"
#include "Timer.h"
#include <vector>
#include <fstream>
#include <ostream>
#include <iostream>
using namespace std;
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
	void createFile();
    void saveToFile();
    void readFromFile();

private:

	int credit;
	int bet;
	int profit;
	int clickForLevel;
	int secondToEnd;
	int gameLevel;


};

#endif /* STATISTICS_H_ */
