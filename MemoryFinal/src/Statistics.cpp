
#include "Statistics.h"

// default Statistics constructor.
Statistics::Statistics() {
	credit = 50;
	bet = 5;
	profit = 0;
	clickForLevel = 0;
	secondToEnd = 0;
	gameLevel = 0;
} // end Statistics constructor.

// default Recovery destructor stub.
Statistics::~Statistics() {

}

//Save second from timer.
void Statistics::setSecondToEnd(int secondToEnd) {
	this->secondToEnd = secondToEnd;
}

//Get second from timer to display on the screen.
int Statistics::getSecondToEnd() const {
	return secondToEnd;
}

//Save how many clicks user make in Game.
void Statistics::setClickForLevel(int clickForLevel) {
	this->clickForLevel = clickForLevel;
}

//Get clicks to display oh the screen.
int Statistics::getClickForLevel() const {
	return clickForLevel;
}

//Save the current level that user reach in Game.
void Statistics::setGameLevel(int gameLevel) {
	this->gameLevel = gameLevel;
}

//Get level to display oh the screen.
int Statistics::getGameLevel() const {
	return gameLevel;
}

//Calculate profit function using seconds, clicks and level.
void Statistics::calculateProfit() {

	if (secondToEnd == 0) {
		profit = 0;
//		credit -= 5;
	}
	else {
		profit = bet + secondToEnd + ((gameLevel + bet) * 2 - clickForLevel);
		if (profit > bet) {
			credit += profit;
		} else {
			credit += bet;
		}
	}
}

//Get profit to display oh the screen.
int Statistics::getProfit() const {
	return profit;
}

//Get credit to display oh the screen.
int Statistics::getCredit() const {
	return credit;
}

//Save credit.
void Statistics::setCredit(int credit) {
	this->credit = credit;
}

//Save last ten game statistics in file.
void Statistics::saveToFile() {
	//Instance of class Statistics that show current property in Game.
	Statistics stat;

	//Vector that save instance of class Statistics
	vector<Statistics> statistics;

	fstream File("files/statistics.dat", ios::in | ios::binary);
	if (File.is_open()) {

		while (!File.eof()) {
			// Read properties current Game from Statistics stat.
			File.read(reinterpret_cast<char*>(&stat), sizeof(Statistics));
			if (!File.eof()) {
				//Push record in vector
				statistics.push_back(stat);
			}
		}
	} else {
		// show message:
		std::cout << "Error ending file";
	}
	File.close();

	//Vector keep only ten records. Erase first record in vector if size go over 10 records.
	if (statistics.size() > 9) {
		statistics.erase(statistics.begin());
	}

	statistics.push_back(*this);

	// Open file for writing
	ofstream newFile("files/statistics.dat", ios::binary | ios::out);

	//Insert ten records from vector in newFile.
	if (newFile.is_open()) {
		for (unsigned int i = 0; i < statistics.size(); i++) {

			newFile.write(reinterpret_cast<char*>(&statistics.at(i)),
					sizeof(Statistics));
		}
	} else {
		// show message:
		std::cout << "Error opening file";
	}

	newFile.close();

}

// Create file statistics.dat function.
void Statistics::createFile() {
	fstream File("files/statistics.dat", ios::in | ios::binary);
}

//This function transfer statistics in Menu - StartBackgroundTexture.
vector<string> Statistics::readFromFile() {

	//Vector content records from file as string.
	vector<string> temp;

	//One record of Statistics
	Statistics stat;

	//Vector with ten record from Statistics
	vector<Statistics> statistics;

	// Open file for reading
	fstream File("files/statistics.dat", ios::in | ios::binary);

	if (File.is_open()) {
		while (!File.eof()) {
			// Read properties current Game from Statistics stat.
			File.read(reinterpret_cast<char*>(&stat), sizeof(Statistics));
			if (!File.eof()) {
				//Push in vector
				statistics.push_back(stat);
			}
		}
	} else {
		// show message:
		std::cout << "Error opening file";
	}
	//Save properties as string
	std::stringstream ss;
	for (unsigned int i = 0; i < statistics.size(); i++) {
		ss << "#";
		ss << i + 1 << ":";
		ss << " Level: ";
		ss << statistics.at(i).getGameLevel();
		ss << "  Clicks: ";
		ss << statistics.at(i).getClickForLevel();
		ss << "  Credits: ";
		ss << statistics.at(i).getCredit();
		ss << "  Win: ";
		ss << statistics.at(i).getProfit();
		ss << "  in ";
		ss << (statistics.at(i).getGameLevel() + 9)
						- statistics.at(i).getSecondToEnd();
		ss << " Seconds";
		//Push strings in vector
		temp.push_back(ss.str());
		ss.str("");

	}

	File.close();

	return temp;
}
