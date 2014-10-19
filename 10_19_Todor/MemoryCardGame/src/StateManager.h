/*
 * StateManager.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Todor
 */

#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_
enum gameStates {

	MENU, STARTGAME, GAMEOVER, RECOVERY, RULES_OF_GAMES, VIEW_CARDS, STATISTIC

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
