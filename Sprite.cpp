#include <assert.h>
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Timer.h"

Sprite::Sprite(){
	m_spriteSheet = nullptr;
	m_cell = 0;
	m_maxCell = 0;
	m_minCell = 0;
	m_maxCellTime = 0.0f;
	m_elapsedCellTime = 0.0f;
}

void Sprite::draw(){
	assert(m_spriteSheet);
	m_spriteSheet->draw(m_cell, m_pos);
}

void Sprite::update(){
	float dt = TheTimer::Instance()->GetDt();

	Vec2f oldVel = m_vel;//remember old velocity
	m_vel += m_acc*dt;
	m_pos += (oldVel + m_vel)*0.5f*dt;

	m_elapsedCellTime += dt;
	if (m_elapsedCellTime >= m_maxCellTime){
		m_elapsedCellTime -= m_maxCellTime;
		m_cell++;
		assert(m_maxCell >= m_minCell);
		if (m_cell > m_maxCell)m_cell = m_minCell;
	}
}

void Sprite::loadAnimation(SpriteSheet* ss, int minCell, int maxCell, float duration){
	m_spriteSheet = ss;
	m_minCell = minCell;
	m_cell = m_minCell;
	m_maxCell = maxCell;
	m_maxCellTime = duration / (m_maxCell - m_minCell);
}

Rect Sprite::getRect() const{
	float w = m_spriteSheet->getCellW();
	float h = m_spriteSheet->getCellH();
	return Rect(m_pos.x, m_pos.x + m_spriteSheet->getCellW(), m_pos.y, m_pos.y + m_spriteSheet->getCellH());
}

void Sprite::setSpriteSheet(SpriteSheet* ss){
	m_spriteSheet = ss;
}

void Sprite::setPos(const Vec2f& pos){
	m_pos = pos;
}

void Sprite::setVel(const Vec2f& vel){
	m_vel = vel;
}

void Sprite::setAcc(const Vec2f& acc){
	m_acc = acc;
}

const Vec2f& Sprite::getPos()const{
	return m_pos;
}

const Vec2f& Sprite::getVel()const{
	return m_vel;
}

const Vec2f& Sprite::getAcc()const{
	return m_acc;
}

const int& Sprite::getCurrentCell()const{
	return m_cell;
}

