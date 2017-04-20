#pragma once

#ifndef Ship_H_
#define Ship_H_

//Std
#include <vector>

//Math includes
#include "MathUtilities.h"
#include "EPhysics.h"

//Game includes
#include "Entities.h"
#include "Bullet.h"

namespace Asteroids 
{
	namespace Entity
	{
		class Ship : public Entities
		{
		public:

			Ship(std::vector<Engine::Math::Vector2D> model_points);
			void Render() override;
		    virtual void RenderLives(unsigned int mode, std::vector<Engine::Math::Vector2D> points, int factor);
			void DrawLives(int lives);
			void MoveForward();
			void MoveRight();
			void MoveLeft();
			void Shoot();
			void Update(float deltaTime) override;
			void Respawn();
			bool canCollide() const { return m_inmune; };
			void setCollision(bool status) { m_inmune = status; };
			void setVelocity(Engine::Math::Vector2D v) { m_velocity = v; };
			Engine::Math::Vector2D getPosition() const { return m_position; };
			void deleteBullet(Bullet*);
			std::vector<Bullet*> m_magazine;
		protected:

			void wrapAround() override;
			void rotate(float num) override;
			void translate(Engine::Math::Vector2D pos) override;

		private:
			void Mass();
			void ResetOrientation();
			float m_currentSpeed;
			Engine::Math::Vector2D m_velocity;
			bool m_inmune;
			Engine::Math::Vector3D m_currentColor;
			int m_respawnTime;
			int m_usedBullets;
			;

		};
	}
}

#endif // !Ship_H_