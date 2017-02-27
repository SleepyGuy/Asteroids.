#include "Ship.hpp"
#include "SDL2\SDL_opengl.h"
#include "Entity.hpp"
#include "Constants.h"
#include "EPhysics.h"
namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;

		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points)
		{
			m_angle = 0.0f;
			m_mass = 2.5f;
		}

		void Ship::MoveUp()
		{
			Engine::Math::Vector2 velocity(m_PlayerSpeed * std::cosf(m_angleInRads), m_PlayerSpeed * std::sinf(m_angleInRads));
			//Engine::Math::Vector2 translateTo = m_ShipPosition + velocity;
			//Engine::Graphics::Drawable2D::Translate(translateTo);
			if (m_mass > 0)
				 {
				float y = (Game::Physics::THRUST / m_mass) * std::sinf(m_angleInRads);
				float x = (Game::Physics::THRUST / m_mass) * std::cosf(m_angleInRads);
			    m_velocity += Engine::Math::Vector2(x, y);
				}
		}
		
		void Ship::MoveLeft()
		{
			Engine::Graphics::Drawable2D::rotate(5.0f);

		}
		void Ship::MoveRight()
		{
			Engine::Graphics::Drawable2D::rotate(-5.0f);
		}

		void Ship::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}
		void Ship::update(float deltaTime)
			 {
						
				float speed = std::fabs(m_velocity.getLength());
				if (speed > Game::Physics::MAX_PLAYER_SPEED)
				  {
				m_velocity = Engine::Math::Vector2
				    (
					(m_velocity.GetX() / 2) * Game::Physics::MAX_PLAYER_SPEED,
					(m_velocity.GetY() / 2) * Game::Physics::MAX_PLAYER_SPEED
					 );
				  }
			
					
				m_velocity = Engine::Math::Vector2(
					m_velocity.GetX() * Game::Physics::DRAG,
					m_velocity.GetY() * Game::Physics::DRAG);
			
							
				Engine::Math::Vector2 pos = m_ShipPosition + m_velocity;
			
							
				  Translate(pos);
			return;
		}
	}
}