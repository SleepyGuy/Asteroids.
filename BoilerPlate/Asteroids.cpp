#include "Asteroids.h"
#include <algorithm>
#include <iostream>
#include "Entities.h"
#include <stdio.h>
#include <windows.h>
#include <cstdlib>

namespace Game 
{
	AsteroidsGame::AsteroidsGame(int WIDTH, int HEIGHT)
		: m_WIDTH(WIDTH)
		, m_HEIGHT(HEIGHT)
		, m_playerIndex(0),
		score(0)
	{}

	AsteroidsGame::~AsteroidsGame() 
	{
		for (int i = 0; i < m_player.size() - 1; i++)
			delete m_player.at(i);

		for (int i = 0; i < m_enemies.size() - 1; i++)
			delete m_enemies.at(i);
	}

	void AsteroidsGame::Init()
	{
		
		Asteroids::Utilities::Load config;
		m_player = config.LoadModels();

		createEnemy(3, Asteroids::Entity::Asteroid::AsteroidSize::BIG, null);

		m_enemyship = new EnemyShip();

		return;
	}

	void AsteroidsGame::Update(float fps)
	{
		m_player[m_playerIndex]->Update(fps);

		for (int i = 0; i < m_enemies.size(); i++)
			m_enemies.at(i)->Update(fps);

		m_enemyship->Update(fps);

		checkCollitions();

		return;
	}
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
	void AsteroidsGame::Render()
	{
		
		
		for (int i = 0; i < m_enemies.size(); i++)
			m_enemies[i]->Render();
		m_player[m_playerIndex]->Render();
		m_player[m_playerIndex]->DrawLives(m_lives);
		this->m_enemyship->Render();

		return;
	}

	void AsteroidsGame::checkCollitions()
	{
		if (!m_player[m_playerIndex]->canCollide()) return;

		int i = 0;
		bool bulletHit = false;
		for (auto temp : m_enemies)
		{
			Asteroids::Entity::Asteroid* pAsteroid = dynamic_cast<Asteroids::Entity::Asteroid*>(temp);
			if (pAsteroid)
			{
				if (m_player[m_playerIndex]->isColliding(pAsteroid))
				{
					Asteroids::Entity::Asteroid::AsteroidSize currentSize = pAsteroid->getSize();
					//
					m_lives = m_lives - 1;
					if (m_lives == 0)
					{
						std::cout << "GAME OVER!!!!!!!!!!!\n";
						std::cout << "\nYoure Score is " << score;
						std::cout << "\n";
						std::cout << "\n";
						exit(1);
					}
				   //
					deleteEnemy(temp);
					
					createDebris(currentSize, m_player[m_playerIndex]->getPosition());
					
					m_player[m_playerIndex]->Respawn();
					break;
				}
				
				for (int i = 0; i < m_player[m_playerIndex]->m_magazine.size(); i++)
				{
					if (m_player[m_playerIndex]->m_magazine[i]->isColliding(pAsteroid))
					{
						
						Asteroids::Entity::Asteroid::AsteroidSize currentSize = pAsteroid->getSize();
						Engine::Math::Vector2D currentPos = pAsteroid->getPosition();

						Score(currentSize);

						deleteEnemy(temp);

						m_player[m_playerIndex]->deleteBullet(m_player[m_playerIndex]->m_magazine[i]);
						
						createDebris(currentSize, currentPos);
						bulletHit = true;
					
					}
				}
				if (bulletHit == true)
				{
					break;
				}

			}
		}
		return;
	}

	void AsteroidsGame::createEnemy(int cant, Asteroids::Entity::Asteroid::AsteroidSize size, Engine::Math::Vector2D pos)
	{
		if (pos == null)
		{
			for (int i = 0; i < cant; i++)
			{
				Asteroids::Entity::Asteroid* nEnemy = new Asteroids::Entity::Asteroid();
				m_enemies.push_back(nEnemy);
			}
			return;
		}

		else
		{
			for (int i = 0; i < cant; i++)
			{
				Asteroids::Entity::Asteroid* nEnemy = new Asteroids::Entity::Asteroid(size, pos);
				m_enemies.push_back(nEnemy);
			}
		}

	}

	void AsteroidsGame::Score(Asteroids::Entity::Asteroid::AsteroidSize size)
	{
		if (size == Asteroids::Entity::Asteroid::AsteroidSize::BIG) 
		{
			score += 100;
		}
		else if (size == Asteroids::Entity::Asteroid::AsteroidSize::MEDIUM) 
		{
			score += 50;
		}
		else
		{
			score += 25;
		}
	}

	void AsteroidsGame::deleteEnemy(Asteroids::Entity::Asteroid* dEnemy) 
	{
		    m_enemies.erase(
			remove(m_enemies.begin(), m_enemies.end(), dEnemy), m_enemies.end()
		);
		delete dEnemy;
	}

	void AsteroidsGame::createDebris(Asteroids::Entity::Asteroid::AsteroidSize size, Engine::Math::Vector2D pos)
	{
		if (size == Asteroids::Entity::Asteroid::AsteroidSize::BIG)
		{
			createEnemy(2, Asteroids::Entity::Asteroid::AsteroidSize::MEDIUM, pos);
		}

		if (size == Asteroids::Entity::Asteroid::AsteroidSize::MEDIUM)
		{
			createEnemy(2, Asteroids::Entity::Asteroid::AsteroidSize::SMALL, pos);
		}
	}
}