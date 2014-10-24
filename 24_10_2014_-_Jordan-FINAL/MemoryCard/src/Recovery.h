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
    void saveRecoverFile( int level, int win, int credit, gameStates state, int clicks );
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
    int m_RecoverCredit;
    gameStates m_RecoverState;
};

#endif /* RECOVERY_H_ */
