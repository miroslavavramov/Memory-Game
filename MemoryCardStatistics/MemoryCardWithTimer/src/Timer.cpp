/*
 * Timer.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: Todor
 */

#include "Timer.h"

Timer::Timer() {
	m_IsStarted = false;
	m_IsFinished = false;
	m_Tick = 0;
	m_CurrentTick = 0;
	m_secToStr = 0;


}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::StartTimer(int ms) {
	m_Interval = ms * 1000;
	m_IsStarted = true;
	m_Tick = SDL_GetTicks();
	m_secToStr = ms;

}



//}
void Timer::StopTimer() {
	m_IsStarted = false;
	m_IsFinished = false;
	m_Tick = 0;

	m_CurrentTick = 0;
}

int Timer::GetSeconds() {
	if (m_IsStarted) {
		m_CurrentTick = SDL_GetTicks();

		if (m_CurrentTick > m_Tick + 1000) {
			m_secToStr--;
			if (m_secToStr == 0) {

				m_IsStarted = false;

			}
			m_Tick = m_CurrentTick;
//			cout<< m_secToStr<< endl;
			return m_secToStr;
		}
	}
	return m_secToStr;
}

std::string Timer::getString() {
	std::stringstream ss;
	std::string tempStr;
	ss << m_secToStr;
	tempStr = ss.str();

	return tempStr;
}


