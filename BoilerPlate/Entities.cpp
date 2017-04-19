#include "Entities.h"

namespace Asteroids
{
	bool Entities::isColliding(Entities* rhs) 
	{
		if (!rhs)
			return false;

		float x = m_position.m_x - rhs->m_position.m_x;
		float y = m_position.m_y - rhs->m_position.m_y;

		float rad = m_radius + rhs->m_radius;
		float distSquared = (x * x) + (y * y);
		return rad * rad >= distSquared;
		
		
		/*if (m_position.GetY() + 100> rhs->m_position.GetY() - 10 &&
			m_position.GetX() + 100> rhs->m_position.GetX() - 10 &&
			rhs->m_position.GetY() + 100 > m_position.GetY() - 100 &&
			rhs->m_position.GetX() - 100 > m_position.GetX() - 100)
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
	}
}