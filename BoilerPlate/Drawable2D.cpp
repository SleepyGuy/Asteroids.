#include "Drawable2D.hpp"
// OPENGL
#include <SDL2\SDL_opengl.h>
#include <iostream>
#include "Ship.hpp"
#include "SDL2\SDL_opengl.h"66
#include "Entity.hpp"
#include "EPhysics.h"
#include  "Constants.h"
namespace Engine
{
	namespace Graphics
	{
		void Drawable2D::Translate(Math::Vector2 position)
		{
			m_ShipPosition = position;
			
		}

		void Drawable2D::Draw(unsigned int drawing_mode, std::vector<Engine::Math::Vector2> model)
		{
			

			glLoadIdentity();
		
			Tranzwarp();
			glTranslatef(m_ShipPosition.GetX(), m_ShipPosition.GetY(), 0.0f);

			glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

			glBegin(drawing_mode);
				for(auto point : model)
				{
					glVertex2f(point.GetX(), point.GetY());
				}				
			glEnd();
			return;
		}
		void Drawable2D::rotate(float num)
		{
						
				m_angle += num;
			    m_angleInRads = (m_angle + Engine::Graphics::ANGLE_OFFSET) * (Engine::Math::PI / 180);
		}
		void Drawable2D::Tranzwarp()
			 {
			if (m_ShipPosition.GetX() > 650)
				{
				   Engine::Math::Vector2 invertedPos(m_ShipPosition.GetX() * -1, m_ShipPosition.GetY() * -1);
				   Translate(invertedPos);
				}
			else if (m_ShipPosition.GetX() < -650)
				 {
				    Engine::Math::Vector2 invertedPos(m_ShipPosition.GetX() * -1, m_ShipPosition.GetY() * -1);
					Translate(invertedPos);
				}
			
				if (m_ShipPosition.GetY() > 400)
				{
					Engine::Math::Vector2 invertedPos(m_ShipPosition.GetX() * -1, m_ShipPosition.GetY() * -1);
					Translate(invertedPos);
				}
			else if (m_ShipPosition.GetY() < -400)
			    {
				Engine::Math::Vector2 invertedPos(m_ShipPosition.GetX() * -1, m_ShipPosition.GetY() * -1);
				Translate(invertedPos);
			    }
			}
	
	}
}