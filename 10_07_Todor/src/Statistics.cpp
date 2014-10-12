#include "Statistics.h"

Statistics::Statistics() {
	// TODO Auto-generated constructor stub
	credit = 50;
	bet = 5;
	profit = 0;
	clickForLevel = 0;
	secondToEnd = 0;
	gameLevel = 0;

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

	if (secondToEnd == 0) {
		profit = -5;
	} else {
		profit =
				((bet * secondToEnd) - (((gameLevel + 2) * 2) - clickForLevel));
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

void Statistics::saveToFile() {
	Statistics stat;
	vector<Statistics> statistics;

	fstream File("files/statistics.dat", ios::in | ios::binary);
	if (File.is_open()) {

		while (!File.eof()) {
			File.read(reinterpret_cast<char*>(&stat), sizeof(Statistics));
			if (!File.eof()) {
				statistics.push_back(stat);
			}
		}
	}
	File.close();
	if (statistics.size() > 9) {
		statistics.erase(statistics.begin());
	}
	statistics.push_back(*this);
	ofstream newFile("files/statistics.dat", ios::binary | ios::out);
	if (newFile.is_open()) {
		for (unsigned int i = 0; i < statistics.size() - 1; i++) {

			newFile.write(reinterpret_cast<char*>(&stat[i]),
					sizeof(Statistics));

		}
	}

	newFile.close();

	/*	ofstream File("files/statistics.dat", ios::app | ios::binary);
	 if (File.is_open()) {

	 File.write(reinterpret_cast<char*>(this), sizeof(*this));

	 }
	 File.close();*/

}

void Statistics::createFile() {
	fstream File("files/statistics.dat", ios::in | ios::binary);
}

void Statistics::readFromFile() {
	Statistics stat;
	vector<Statistics> statistics;

	fstream File("files/statistics.dat", ios::in | ios::binary);
	if (File.is_open()) {

		while (!File.eof()) {
			File.read(reinterpret_cast<char*>(&stat), sizeof(Statistics));
			if (!File.eof()) {
				statistics.push_back(stat);
			}
		}
	}
	File.close();
//	if (statistics.size() > 9) {
//		statistics.erase(statistics.begin());
//	}
//	for (unsigned i = 0; i < statistics.size(); i++) {
//		cout << "size" << statistics.size() << endl << endl;
//		cout << statistics[i].bet << endl;
//		cout << statistics[i].clickForLevel << endl;
//		cout << statistics[i].credit << endl;
//		cout << statistics[i].profit << endl;
//
//	}
}
