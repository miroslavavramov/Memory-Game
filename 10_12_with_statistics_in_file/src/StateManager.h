/*
 * StateManager.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Todor
 */

#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_
enum gameStates{

	MENU = 0,
	STARTGAME = 1,
	GAMEOVER = 2,
	RECOVERY = 3,
	TEAM_PROJECT = 4,
	RULES_OF_GAMES = 5,
	VIEW_CARDS =6,
	STATISTIC

};

class StateManager {
public:
	static StateManager* stateMachine;
	StateManager();
	virtual ~StateManager();
	gameStates getCurrentGameStates() const;
	void setCurrentGameStates(gameStates currentGameStates);
private:
	gameStates m_currentGameStates;
};

#endif /* STATEMANAGER_H_ */
