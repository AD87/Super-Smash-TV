#include "Rect.h"
#include "Vec2.h"

Rect::Rect(){
	m_minX = 0;
	m_maxX = 0;
	m_minY = 0;
	m_maxY = 0;
}

Rect::Rect(float minX, float maxX, float minY, float maxY){
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
}

bool Rect::intersects(const Rect& otherRect)const{
	return ((m_maxX > otherRect.m_minX) && (otherRect.m_maxX > m_minX) &&
		(m_maxY > otherRect.m_minY) && (otherRect.m_maxY > m_minY));
}

Rect Rect::scale(float number)const{
	Vec2f centre((m_maxX + m_minX)*0.5f, (m_maxY + m_minY)*0.5f);
	float w = m_maxX - m_minX;
	float h = m_maxY - m_minY;
	return Rect(centre.x - w*0.5f*number, centre.x + w*0.5f*number,
		centre.y - h*0.5f*number, centre.y + h*0.5f*number);
}
