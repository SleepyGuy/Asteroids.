#include "Ship.hpp"
#include <SDL2\SDL_opengl.h>
#include "Entity.hpp"
namespace Asteroids
{
	namespace Entities
	{
		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points)
		{}

		void Ship::MoveUp()
		{
			Engine::Math::Vector2 velocity = Engine::Math::Vector2(0, 1);
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
			Engine::Math::Vector2 velocity = Engine::Math::Vector2(-1, 0);
			Engine::Math::Vector2 newPos =
				m_position + velocity;

			Entity::Translate(newPos);
		}
		void Ship::MoveRight()
		{
			Engine::Math::Vector2 velocity = Engine::Math::Vector2(1,0);
			Engine::Math::Vector2 newPos =
				m_position + velocity;

			Entity::Translate(newPos);
		}

		void Ship::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}
	}
}