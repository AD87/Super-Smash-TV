#include "Bullet.h"
#include "Screen.h"

void Bullet::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}

void Bullet::setVel(const Vec2f& vel){
	m_sprite.setVel(vel);
}

void Bullet::checkOffScreen(){
	float maxX = static_cast<float> (TheScreen::Instance()->getSize().x);
	float maxY = static_cast<float> (TheScreen::Instance()->getSize().y);

	if (m_sprite.getPos().x <= 0 || m_sprite.getPos().x >= maxX || 
			m_sprite.getPos().y <= 0 || m_sprite.getPos().y >= maxY){
		RemoveMe();
	}
}