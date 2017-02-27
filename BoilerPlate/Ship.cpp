#include "Ship.hpp"
#include <SDL2\SDL_opengl.h>
#include <cmath>
#include "Constants.hpp"
#include <iostream>

namespace Asteroids
{
	namespace Entities
	{
		//Constants
		const int WIDTH = 1280;
		const int HEIGHT = 720;
		const float ANGLE_OFFSET = 90.0f;
		const float DRAG = 1.0f;
		const float THRUST = 25.5f;
		const float MAX_SPEED = 1000.0f;

		inline float teleport(float axis, float min, float max)
		{
			if (axis < min)
			{
				return max - (min - axis);
			}

			if (axis > max)
			{
				return min + (axis - max);
			}

			return axis;
		}

		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points), m_mass(0.5f)
		{
			m_angle = 0.0f;
			m_angleinRads = ANGLE_OFFSET * (Engine::Math::PI / 180);
		}

		void Ship::MoveUp()
		{
			//Impulse
			if (m_mass > 0)
			{
				float x = (THRUST / m_mass) * std::cosf(m_angleinRads);
				float y = (THRUST / m_mass) * std::sinf(m_angleinRads);
				m_velocity += Engine::Math::Vector2(x, y);
			}
		}

		void Ship::MoveDown()
		{
			float x = (THRUST / m_mass) * std::cosf(m_angleinRads);
			float y = (THRUST / m_mass) * std::sinf(m_angleinRads);
			m_velocity -= Engine::Math::Vector2(x, y);
		}

		void Ship::MoveLeft()
		{
			m_angle += 9.5f;
			m_angleinRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);
			
		}

		void Ship::MoveRight()
		{
			m_angle -= 9.5f;
			m_angleinRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);
			
		}


		void Ship::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}
		
		

		void Ship::Update(float omega)
		{
			//SPEED LIMIT
			float speed = std::fabs(m_velocity.Length());

			if (speed > MAX_SPEED)
			{
				
				m_velocity = Engine::Math::Vector2(
					(m_velocity.GetX() / speed) * MAX_SPEED ,
					(m_velocity.GetY() / speed) * MAX_SPEED 
					);

				speed = std::fabs(m_velocity.Length());
				
			}
			

			//Drag Effect 
			m_velocity = Engine::Math::Vector2(
				m_velocity.GetX() * DRAG,
				m_velocity.GetY() * DRAG 
				);
				
			//X,Y Position 
			Engine::Math::Vector2 newPos(
				m_position.GetX() + (m_velocity.GetX() * omega),
				m_position.GetY() + (m_velocity.GetY() * omega)
				);

			// Tranzwarp
			float HalfWidth = (WIDTH / 2);
			float HalfHeight = (HEIGHT / 2);
			float MinX = -HalfWidth;
			float MaxX = HalfWidth;
			float MinY = -HalfHeight;
			float MaxY = HalfHeight;

			float x = teleport(newPos.GetX(), MinX, MaxX);
			float y = teleport(newPos.GetY(), MinY, MaxY);

			
			newPos = Engine::Math::Vector2(x, y);

			Entity::Translate(newPos);

		}

	}
}