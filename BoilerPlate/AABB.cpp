#include "AABB.h"

AABB::AABB()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

AABB::AABB(int x, int y, int width, int heigth)
	:m_x(x), m_y(y), m_width(width), m_height(heigth)
{
}

bool AABB::isColliding(AABB * rhs)
{
	return (GetMinX() < rhs->GetMaxX() && GetMaxX()> rhs->GetMinX() &&
		GetMinY() < rhs->GetMaxY() && GetMaxY() > rhs->GetMinY());
}

int AABB::GetX()
{
	return m_x;
}

int AABB::GetY()
{
	return m_y;
}

int AABB::GetWidth()
{
	return m_width;
}

int AABB::GetHeight()
{
	return m_height;
}

int AABB::GetMinX()
{
	return m_x - (m_width / 2);
}

int AABB::GetMinY()
{
	return m_y - (m_height / 2);
}

int AABB::GetMaxX()
{
	return m_x + m_width;
}

int AABB::GetMaxY()
{
	return m_y + m_height;
}

int AABB::SetX(int value)
{
	return m_x = value;
}

int AABB::SetY(int value)
{
	return m_y = value;
}

void AABB::Update(int x, int y)
{
	m_x = x;
	m_y = y;
}

