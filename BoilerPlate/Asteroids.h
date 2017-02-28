#pragma once
#ifndef _Asteroids_H_
#define _Asteroids_H_

// STD
#include <vector>

//
#include "Vector2.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Utils.h"

namespace Game 
{
	const Engine::Math::Vector2D null(0.f, 0.f);

	class AsteroidsGame 
	{
	public:
		AsteroidsGame(int WIDTH, int HEIGHT);
		~AsteroidsGame();
		void Init();
		void Update(float fps);
		void Render();

		std::vector<Asteroids::Entity::Ship*>				m_player;
		int													m_playerIndex;
		std::vector<Asteroids::Entity::Asteroid*>			m_enemies;

	private:
		int								m_WIDTH;
		int								m_HEIGHT;
		void checkCollitions();
		void deleteEnemy(Asteroids::Entity::Asteroid*);
		void createDebris(Asteroids::Entity::Asteroid::AsteroidSize size, Engine::Math::Vector2D pos);
		void createEnemy(int, Asteroids::Entity::Asteroid::AsteroidSize, Engine::Math::Vector2D);
	};
}

#endif // !_Asteroids_H_