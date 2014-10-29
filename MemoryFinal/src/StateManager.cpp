/*
 * StateManager.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Todor
 */

#include "StateManager.h"

StateManager::StateManager() {
	// TODO Auto-generated constructor stub
	m_currentGameStates = MENU;
}

StateManager::~StateManager() {
	// TODO Auto-generated destructor stub
}

gameStates StateManager::getCurrentGameStates() const {
	return m_currentGameStates;
}

void StateManager::setCurrentGameStates(gameStates currentGameStates) {
	m_currentGameStates = currentGameStates;
}
