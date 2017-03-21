#pragma once
#ifndef _AABB_
#define _AABB_
class AABB
{
public:
	AABB();
	AABB(int x, int y, int width, int heigth);
	bool isColliding(AABB* rhs);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	int GetMinX();
	int GetMinY();
	int GetMaxX();
	int GetMaxY();
	int SetX(int value);
	int SetY(int value);
	void Update(int x, int y);
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};
#endif