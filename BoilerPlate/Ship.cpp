#include "Ship.hpp"
#include "SDL2\SDL_opengl.h"66
#include "Entity.hpp"
#include "Constants.h"
namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;
		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points)
		{
			m_angle = 0.0f;
		}

		void Ship::MoveUp()
		{
			Engine::Math::Vector2 velocity(
				std::cosf((m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180)),
				std::sinf((m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180))
			);
			Engine::Math::Vector2 newPos =
				m_position + velocity;

			Entity::Translate(newPos);
		}
		void Ship::MoveDown()
		{
			Engine::Math::Vector2 velocity = Engine::Math::Vector2(0,-1);
			Engine::Math::Vector2 newPos =
				m_position + velocity;

			Entity::Translate(newPos);
		}
		void Ship::MoveLeft()
		{
			m_angle += 5.0f;

		}
		void Ship::MoveRight()
		{
			m_angle -= 5.0f;
		}

		void Ship::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}
	}
}