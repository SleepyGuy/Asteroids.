#pragma once
#ifndef _H_Asteroid_
#define	_H_Asteroid_

#include "Entities.h"

namespace Asteroids
{
	namespace Entity
	{
		const int MAX_POINTS = 12;
		const float MIN_SIZE = 25.f;
		const float MAX_SIZE = 45.f;

		class Asteroid : public Entities
		{
		public:
			enum AsteroidSize
			{
				BIG = 0,
				MEDIUM = 1,
				SMALL = 2
			};
			Asteroid();
			Asteroid(AsteroidSize, Engine::Math::Vector2D);
			void Render() override;
			void Update(float deltaTime) override;
			AsteroidSize getSize() const { return m_size; };
			Engine::Math::Vector2D getPosition() const { return m_position; };

		protected:
			void wrapAround() override;
			void rotate(float num) override;
			void translate(Engine::Math::Vector2D pos) override;

		private:

			AsteroidSize m_size;
			int sizeFactor;
			void randomPoints();
			void randomPos(float max, float min);
			void randomAngle(float max, float min);
		};
	}
}

#endif //!_H_Asteroid_