/*
 * Timer.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Miroslav Avramov
 */

#include "Timer.h"

// default Timer constructor
Timer::Timer() {
	m_IsStarted = false;
	m_IsFinished = false;
	m_Tick = 0;
	m_CurrentTick = 0;
	m_secToStr = 0;
	m_Interval = 0;

}//end Recovery constructor

// default Recovery destructor stub
Timer::~Timer() {

}

//Start timer give 3 second in state GAMEOVER and 10 seconds in state VIEW_CARDS in Game.
void Timer::StartTimer(int ms) {
	m_Interval = ms * 1000;
	m_IsStarted = true;
	m_Tick = SDL_GetTicks();
	m_secToStr = ms;
}

//Stop timer
void Timer::StopTimer() {
	m_IsStarted = false;
	m_IsFinished = false;
	m_Tick = 0;
	m_CurrentTick = 0;
}

//Calculate time
int Timer::GetSeconds() {
	if (m_IsStarted) {
		m_CurrentTick = SDL_GetTicks();

		//Compare too ticks to get second.
		if (m_CurrentTick > m_Tick + 1000) {
			m_secToStr--;
			if (m_secToStr == 0) {

				m_IsStarted = false;
			}
			m_Tick = m_CurrentTick;
			return m_secToStr;
		}
	}

	return m_secToStr;
}

//Return second as string.
std::string Timer::getString() {
	std::stringstream ss;
	std::string tempStr;
	ss << m_secToStr;
	tempStr = ss.str();

	return tempStr;
}
