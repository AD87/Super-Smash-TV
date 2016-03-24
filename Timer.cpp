#include "Timer.h"
#include <SDL.h>

Timer::Timer(){
	m_dt = 0;
	m_prevTicks = 0;
}

void Timer::Update(){
	unsigned int currentTicks = SDL_GetTicks();
	unsigned int dtMs = currentTicks - m_prevTicks;
	m_prevTicks = currentTicks;
	m_dt = static_cast<float>(dtMs) / 1000.0f;
	const float MAX_DT = 0.05f;
	if (m_dt > MAX_DT) m_dt = MAX_DT;
}

float Timer::GetDt()const{
	return m_dt;
}