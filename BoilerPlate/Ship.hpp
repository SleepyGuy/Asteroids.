#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

//
#include <vector>

//
#include "Vector2.hpp"
#include "Entity.hpp"
#include "EPhysics.h"


namespace Asteroids
{
	namespace Entities
	{
		class Ship : public Entity
		{
		public:
			/*
			 * CONS
			 */
			Ship(const std::vector<Engine::Math::Vector2> points);

			/*
			 * FUNCTIONS
			 */
			void MoveUp();
			void MoveLeft();
			void MoveRight();
			void Draw();
			void update(float deltaTime);
		private:
			std::vector<Engine::Math::Vector2> m_points;
			float m_mass;
			Engine::Math::Vector2 m_velocity;
			
		};
	}
}

#endif // !_SHIP_H_
