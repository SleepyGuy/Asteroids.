#include "Bullet.h"

#include "EPhysics.h"
#include "SDL2\SDL_opengl.h"

namespace Asteroids 
{
	namespace Entity 
	{
		Bullet::Bullet(Engine::Math::Vector2D pos, Engine::Math::Vector2D v, float angle)
		{
			m_mass = 0.3f;
			m_radius = 7.f;
			m_angle = angle;
			m_angleInRads = (m_angle + Asteroids::angle_offset) * (Engine::Math::PI / 180);
			m_position = pos;
			m_lifeTime = 0;
		};
		
		void Bullet::Render() 
		{
			m_lifeTime++;

			//
			glLoadIdentity();
			Tranzwarp();

			glTranslatef(m_position.m_x, m_position.m_y, 0.f);

			glColor3f(1, 1, 1);

			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
				int limit = 100;
				for (int idx = 0; idx < limit; idx++)
				{
					float bullet =0.2f * Engine::Math::PI * float(idx) / float(limit);
					float x = m_radius * cosf(bullet);
					float y = m_radius * sinf(bullet);
					Engine::Math::Vector2D vertex(
						x + m_position.m_x, 
						y + m_position.m_y);
					glVertex2f(vertex.m_x, vertex.m_y);
				}
			glEnd();
		};

		void Bullet::Update(float fps) 
		{
			
			Engine::Math::Vector2D current;
			if (m_mass > 0)
			{
				float impulse = (Physics::THRUST / m_mass);
				float x = impulse * std::cosf(m_angleInRads);
				float y = impulse * std::sinf(m_angleInRads);

				current += Engine::Math::Vector2D(x, y);
			}
			
			current += m_position;
			translate(current);
			return;
		};

		void Bullet::Tranzwarp()
		{
			if (m_position.m_x > 650)
			{
				Engine::Math::Vector2D reversePos(m_position.m_x * -1, m_position.m_y * -1);
				translate(reversePos);
			}
			else if (m_position.m_x < -650)
			{
				Engine::Math::Vector2D reversePos(m_position.m_x * -1, m_position.m_y * -1);
				translate(reversePos);
			}

			if (m_position.m_y > 400)
			{
				Engine::Math::Vector2D reversePos(m_position.m_x * -1, m_position.m_y * -1);
				translate(reversePos);
			}
			else if (m_position.m_y < -400)
			{
				Engine::Math::Vector2D reversePos(m_position.m_x * -1, m_position.m_y * -1);
				translate(reversePos);
			}
		};
	}
}