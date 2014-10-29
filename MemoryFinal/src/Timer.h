/*
 * Timer.h
 *
 *  Created on: Oct 4, 2014
 *      Author: User
 */
#ifndef TIMER_H_
#define TIMER_H_

// C++ standard library includes
#include <string>
#include <sstream>

//SDL2 standard library includes
#include <SDL.h>

using namespace std;

class Timer {
public:
	Timer();
	virtual ~Timer();
	void StartTimer(int ms);
	void StopTimer();
	bool GetIsStarted(){ return m_IsStarted; }
	bool GetIsFinished() { return m_IsFinished; }
    int GetSeconds();
    std::string  getString();
   static Timer* g_Timer;
private:

	bool m_IsStarted;
	bool m_IsFinished;
	int m_Tick;
	int m_CurrentTick;
	int m_Interval;
	int m_secToStr;

};

#endif /* TIMER_H_ */
