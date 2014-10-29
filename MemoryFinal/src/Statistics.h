
#ifndef STATISTICS_H_
#define STATISTICS_H_

// C++ standard library includes
#include <vector>
#include <fstream>
#include <ostream>

// Custom includes
#include "Card.h"
#include "Timer.h"

using namespace std;

class Statistics {
public:
	Statistics();
	virtual ~Statistics();

	void calculateProfit();

	//Accessory functions for clicks in every level.
	int getClickForLevel() const;
	void setClickForLevel(int clickForLevel);

	//Accessory functions for seconds to end.
	int getSecondToEnd() const;
	void setSecondToEnd(int secondToEnd);

	//Accessory functions for game level.
	void setGameLevel(int gameLevel);
	int getGameLevel() const;

	//Accessory functions for profit.
	int getProfit() const;

	//Accessory functions for credit.
	int getCredit() const;
	void setCredit(int credit);

	// Create file statistics.dat function.
	void createFile();

	//Save last ten game statistics in file.
    void saveToFile();
    vector<string> readFromFile();

private:

	int credit;
	int bet;
	int profit;
	int clickForLevel;
	int secondToEnd;
	int gameLevel;


};

#endif /* STATISTICS_H_ */
