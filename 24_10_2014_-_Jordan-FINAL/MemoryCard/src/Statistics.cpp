#include "Statistics.h"
#include <iostream>

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
		profit = 0;
		credit += -5;
	} else {
		profit = 5 + secondToEnd + ((gameLevel + 5) * 2 - clickForLevel);
		if (profit > 5) {
			credit += profit;
		} else {
			credit += 5;
		}

	}
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
		for (unsigned int i = 0; i < statistics.size(); i++) {

			newFile.write(reinterpret_cast<char*>(&statistics.at(i)),
					sizeof(Statistics));

		}
	}

	newFile.close();

}

void Statistics::createFile() {
	fstream File("files/statistics.dat", ios::in | ios::binary);
}

vector<string> Statistics::readFromFile() {
	vector<string> temp;
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
		ss
				<< (statistics.at(i).getGameLevel() + 9)
						- statistics.at(i).getSecondToEnd();
		ss << " Seconds";
		temp.push_back(ss.str());
		ss.str("");

	}

	File.close();

	return temp;

}
