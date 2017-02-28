#include "Asteroid.h"

#include <time.h>

#include "SDL2\SDL_opengl.h"

#include "MathUtilities.h"
#include "EPhysics.h"

namespace Asteroids
{
	namespace Entity
	{
		Asteroid::Asteroid()
		{
			m_mass = 0.7f;
			m_size = Asteroid::BIG;
			sizeFactor = static_cast<int> (m_size);
			randomPoints();
			randomPos(350, 600);
			randomAngle(2, 24);
			m_angleInRads = (m_angle + Asteroids::angle_offset) * (Engine::Math::PI / 180);

			if (m_size == AsteroidSize::BIG)
				m_radius = 80.f;
			
			if (m_size == AsteroidSize::MEDIUM)
				m_radius = 40.f;

			if (m_size == AsteroidSize::SMALL)
				m_radius = 20.f;

			
		}

		Asteroid::Asteroid(AsteroidSize size, Engine::Math::Vector2D pos) 
		{
			m_points.resize(MAX_POINTS);
			m_size = size;
			m_position = pos;
			randomPoints();
			randomAngle(2, 24);
			m_angleInRads = (m_angle + Asteroids::angle_offset) * (Engine::Math::PI / 180);

			if (m_size == AsteroidSize::BIG) { m_radius = 80.f; m_mass = 2.f; };

			if (m_size == AsteroidSize::MEDIUM) { m_radius = 40.f; m_mass = 1.2f; };

			if (m_size == AsteroidSize::SMALL) { m_radius = 20.f; m_mass = 0.8f; };

			
		};

		void Asteroid::Render() 
		{

			
			glLoadIdentity();
			
			wrapAround();
			
			glTranslatef(m_position.m_x, m_position.m_y, 0.0f);

			glColor3f(1, 1, 1);
			
			glBegin(GL_LINE_LOOP);
			for (auto temp : m_points)
			{
				glVertex2f(temp.m_x, temp.m_y);
			}
			glEnd();

			return;
		};
		
		void Asteroid::Update(float deltaTime) 
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

		void Asteroid::wrapAround() 
		{
			if (m_position.m_x > 650)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
			else if (m_position.m_x < -650)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}

			if (m_position.m_y > 400)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
			else if (m_position.m_y < -400)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
		}

		void Asteroid::rotate(float num) 
		{
			m_angle += num;
		}

		void Asteroid::translate(Engine::Math::Vector2D pos) 
		{
			m_position = pos;
			return;
		}

		void Asteroid::randomPoints() 
		{
			int sizeFactor = static_cast<int>(m_size) + 1;
			float min = MIN_SIZE / sizeFactor;
			float max = MAX_SIZE / sizeFactor;

			for (int licount = 0; licount < MAX_POINTS; ++licount)
			{
				const float radians = (licount / static_cast<float>(MAX_POINTS)) * 1.5f * Engine::Math::PI;
				const float randDist = Engine::Math::RandomInRange<float>(min, max);

				m_points.push_back(Engine::Math::Vector2D(sinf(radians) * randDist, cosf(radians) * randDist));
			}
		}

		void Asteroid::randomPos(float Ymax, float Xmax) 
		{
			float x = Engine::Math::RandomInRange<float>(-Xmax, Xmax);
			float y = Engine::Math::RandomInRange<float>(-Ymax, Ymax);

			m_position.m_x = x;
			m_position.m_y = y;
		};

		void Asteroid::randomAngle(float min, float max) 
		{
			m_angle = Engine::Math::RandomInRange<float>(min, max);
		};
	}
}