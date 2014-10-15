/*
 * Recovery.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#include "Recovery.h"

Recovery::Recovery() {
	// TODO Auto-generated constructor stub

}

Recovery::~Recovery() {
	// TODO Auto-generated destructor stub
}

void Recovery::createRecoverFile() {
	fstream File("files/recover.dat", ios::in | ios::binary);
}

void Recovery::saveRecoverFile(int level, int win, int credit, int time, gameStates state, vector <Card> Cards, int clicks ) {

    m_RecoverLevel = level;
    m_RecoverWin = win;
    m_RecoverCredit = credit;
    m_RecoverTime = time;
    m_RecoverState = state;
    m_RecoverCards = Cards;
    m_RecoverClicks = clicks;

	ofstream newFile("files/recover.dat", ios::binary | ios::out);
	if (newFile.is_open()) {
			newFile.write(reinterpret_cast<char*>(this),sizeof(Recovery));
	}

	newFile.close();
}

Recovery& Recovery::LoadRecoverFile() {

	fstream File("files/recover.dat", ios::in | ios::binary);
	if (File.is_open()) {

		while (!File.eof()) {
			File.read(reinterpret_cast<char*>(this), sizeof(Recovery));
		}
	}
	File.close();
	return *this;
}

const vector<Card>& Recovery::getRecoverCards() const {
	return m_RecoverCards;
}

void Recovery::setRecoverCards(const vector<Card>& recoverCards) {
	m_RecoverCards = recoverCards;
}

int Recovery::getRecoverClicks() const {
	return m_RecoverClicks;
}

void Recovery::setRecoverClicks(int recoverClicks) {
	m_RecoverClicks = recoverClicks;
}

int Recovery::getRecoverCredit() const {
	return m_RecoverCredit;
}

void Recovery::setRecoverCredit(int recoverCredit) {
	m_RecoverCredit = recoverCredit;
}

int Recovery::getRecoverLevel() const {
	return m_RecoverLevel;
}

void Recovery::setRecoverLevel(int recoverLevel) {
	m_RecoverLevel = recoverLevel;
}

gameStates Recovery::getRecoverState() const {
	return m_RecoverState;
}

void Recovery::setRecoverState(gameStates recoverState) {
	m_RecoverState = recoverState;
}

int Recovery::getRecoverTime() const {
	return m_RecoverTime;
}

void Recovery::setRecoverTime(int recoverTime) {
	m_RecoverTime = recoverTime;
}

int Recovery::getRecoverWin() const {
	return m_RecoverWin;
}

void Recovery::setRecoverWin(int recoverWin) {
	m_RecoverWin = recoverWin;
}
