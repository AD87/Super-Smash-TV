#pragma once

class Rect{
public:
	Rect();
	Rect(float minX, float maxX, float minY, float maxY);
	bool intersects(const Rect& otherRect)const;
	Rect scale(float number) const;

private:
	float m_minX;
	float m_maxX;
	float m_minY;
	float m_maxY;
};