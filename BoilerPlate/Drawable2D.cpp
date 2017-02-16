#include "Drawable2D.hpp"
// OPENGL
#include <SDL2\SDL_opengl.h>
#include <iostream>
namespace Engine
{
	namespace Graphics
	{
		void Drawable2D::Translate(Math::Vector2 position)
		{
			m_position = position;
		}

		void Drawable2D::Draw(unsigned int mode, std::vector<Math::Vector2> points)
		{
			Tranzwarp();

			glLoadIdentity();
		
			glTranslatef(m_position.GetX(), m_position.GetY(), 0.0f);

			glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

			glBegin(mode);
				for(auto point : points)
				{
					glVertex2f(point.GetX(), point.GetY());
				}				
			glEnd();
		}
		void Drawable2D::Tranzwarp()
			 {
			if (m_position.GetX() > 650)
				{
				m_position.setX(m_position.GetX() * -1);
				m_position.setY(m_position.GetY() * -1);
				}
			else if (m_position.GetX() < -650)
				 {
				m_position.setX(m_position.GetX() * -1);
				m_position.setY(m_position.GetY() * -1);
				}
			
				if (m_position.GetY() > 400)
				{
					m_position.setX(m_position.GetX() * -1);
					m_position.setY(m_position.GetY() * -1);
				}
			else if (m_position.GetY() < -400)
			    {
				m_position.setX(m_position.GetX() * -1);
				m_position.setY(m_position.GetY() * -1);
			    }
			}
	}
}