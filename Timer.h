#pragma once
#include "Singleton.h"

class Timer:public Uncopyable{
private:
	Timer();
	friend Singleton<Timer>;
public:

	void Update();
	float GetDt() const;
private:
	float m_dt;
	unsigned int m_prevTicks;
};

typedef Singleton<Timer> TheTimer;