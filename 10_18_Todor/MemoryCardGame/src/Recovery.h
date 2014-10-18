/*
 * Recovery.h
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#ifndef RECOVERY_H_
#define RECOVERY_H_
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include "Card.h"
#include "StateManager.h"
using namespace std;

class Recovery {
public:
	Recovery();
	virtual ~Recovery();
	void createRecoverFile();
    void saveRecoverFile( int level, int win, int credit, int time, gameStates state, vector <Card> Cards, int clicks );
    Recovery& LoadRecoverFile();
	const vector<Card>& getRecoverCards() const;
	void setRecoverCards(const vector<Card>& recoverCards);
	int getRecoverClicks() const;
	void setRecoverClicks(int recoverClicks);
	int getRecoverCredit() const;
	void setRecoverCredit(int recoverCredit);
	int getRecoverLevel() const;
	void setRecoverLevel(int recoverLevel);
	gameStates getRecoverState() const;
	void setRecoverState(gameStates recoverState);
	int getRecoverTime() const;
	void setRecoverTime(int recoverTime);
	int getRecoverWin() const;
	void setRecoverWin(int recoverWin);

private:
    int m_RecoverLevel;
    int m_RecoverWin;
    int m_RecoverCredit;
    int m_RecoverTime;
    gameStates m_RecoverState;
    vector <Card> m_RecoverCards;
    int m_RecoverClicks;
};

#endif /* RECOVERY_H_ */
