/*
 * Timer.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Todor
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <SDL.h>
#include <string>
#include <sstream>
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
