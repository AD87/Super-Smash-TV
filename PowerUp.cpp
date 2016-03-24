#include "PowerUp.h"
#include "Timer.h"

void PowerUp::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}

void PowerUp::draw(){
	m_sprite.draw();
}

void PowerUp::update(){
	m_sprite.update();
	m_timeRemaining -= TheTimer::Instance()->GetDt();
	if (m_timeRemaining <= 0){
		this->RemoveMe();//all powerUps most be collected within 5 seconds or they will dissapear
	}
}

const Rect& PowerUp::getRect() const {
	return m_sprite.getRect();
}