#include "Asteroid.h"

#include <SDL2/SDL_opengl.h>

#include "Constants.hpp"
#include "MathUtilities.hpp"
#include <iostream>

namespace Asteroids
{
	namespace Entities
	{
		const int NUM_POINTS = 16;
		const float MIN_SIZE = 25.0f;
		const float MAX_SIZE = 40.0f;
		const int WIDTH = 1366;
		const int HEIGHT = 768;
		const float AST_THRUST = 5.0f;
		const float MAX_SPEED = 100.0f;
		const float m_mass = 2.0f;
		
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

		Asteroid::Asteroid(const std::vector<Engine::Math::Vector2> points) : m_points(points)
		{

		}

		void Asteroid::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}

		void Asteroid::Update(float omegaTime)
		{
			float speed = std::fabs(m_velocity.Length());
			if (speed > MAX_SPEED)
			{
					m_velocity = Engine::Math::Vector2(
					(m_velocity.GetX() / speed) * MAX_SPEED,
					(m_velocity.GetY() / speed) * MAX_SPEED
				);

				speed = std::fabs(m_velocity.Length());

			}

			float x = (AST_THRUST / m_mass) * std::cosf(m_angleinRads);
			float y = (AST_THRUST / m_mass) * std::sinf(m_angleinRads);
			m_velocity += Engine::Math::Vector2(x, y);

			Engine::Math::Vector2 newPos(
				m_position.GetX() + (m_velocity.GetX() * omegaTime),
				m_position.GetY() + (m_velocity.GetY() * omegaTime)
			);

			float HalfWidth = (WIDTH / 2);
			float HalfHeight = (HEIGHT / 2);
			float MinX = -HalfWidth;
			float MaxX = HalfWidth;
			float MinY = -HalfHeight;
			float MaxY = HalfHeight;

			float z = teleport(newPos.GetX(), MinX, MaxX);
			float w = teleport(newPos.GetY(), MinY, MaxY);


			newPos = Engine::Math::Vector2(z, w);

			Entity::Translate(newPos);
		}
	}
}