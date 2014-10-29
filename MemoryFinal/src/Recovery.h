/*
 * Recovery.h
 *
 *  Created on: Oct 2, 2014
 *      Author: User
 */

#ifndef RECOVERY_H_
#define RECOVERY_H_

// C++ standard library includes
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>

// Custom includes
#include "Card.h"
#include "StateManager.h"

class Recovery {
public:
	Recovery();
	virtual ~Recovery();
	void createRecoverFile();
    void saveRecoverFile(int level, int credit, gameStates state);
    void LoadRecoverFile();

    //Accessory function for credit.
	int getRecoverCredit() const;

	//Accessory function for level.
	int getRecoverLevel() const;

	//Accessory function for state.
	gameStates getRecoverState() const;


private:
    int m_RecoverLevel;
    int m_RecoverCredit;
    gameStates m_RecoverState;
};

#endif /* RECOVERY_H_ */
