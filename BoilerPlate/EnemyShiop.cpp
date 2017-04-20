#include "EnemyShip.h"
#include <SDL2\SDL_opengl.h>
#include "Entities.h"
#include "EPhysics.h"
#include "Ship.h"
#include <algorithm>
EnemyShip::EnemyShip()
{
	GeneratePoints();
	x = 400;
	Position = Vector2D(-400, -75);
	m_usedBullets = 0;
}

void EnemyShip::Render()
{
	glLoadIdentity();

	
	glTranslatef(Position.GetX(), Position.GetY(), 0.0f);

	glRotatef(0, 0.0f, 0.0f, 0.0f);

	glColor3f(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	for (auto temp : m_points)
	{
		glVertex2f(temp.m_x, temp.m_y);
	}
	glEnd();

	for (int i = 0; i < m_magazine.size(); i++)
		m_magazine[i]->Render();
}

void EnemyShip::Update(float deltaTime)
{
	x += 0.015f;
	float y = 2 * (cosf(x) * (270 / PI));
	Position = Vector2D(x, y);

	Shoot();

	for (int i = 0; i < m_magazine.size(); i++)
	{
		m_magazine[i]->Update(deltaTime);
		if (m_magazine[i]->m_lifeTime >= 240)
		{
			deleteBullet(m_magazine[i]);
			break;
		}
	}
	return;
	
}

void EnemyShip::Shoot()
{
	if (m_usedBullets == 5) return;
	else if (m_usedBullets < 5)
	{
		Asteroids::Entity::Bullet* nBullet = new Asteroids::Entity::Bullet(Position, Vector2D(30,30), m_angle);
		m_magazine.push_back(nBullet);
		m_usedBullets++;
	}
}

void EnemyShip::GeneratePoints()
{
	Entities::m_points.push_back(Vector2D(-14.0, -12.0));
	Entities::m_points.push_back(Vector2D(14.0, -10.0));
	Entities::m_points.push_back(Vector2D(24.0, 0.0));
	Entities::m_points.push_back(Vector2D(14.0, 12.0));
	Entities::m_points.push_back(Vector2D(8.0, 12.0));
	Entities::m_points.push_back(Vector2D(2.0, 20.0));
	Entities::m_points.push_back(Vector2D(-2.0, 24.0));
	Entities::m_points.push_back(Vector2D(-8.0, 12.0));
	Entities::m_points.push_back(Vector2D(-14.0, 10.0));
	Entities::m_points.push_back(Vector2D(-24.0, 0.0));
}

void EnemyShip::deleteBullet(Asteroids::Entity::Bullet* dBullet)
{
	m_magazine.erase(
		remove(m_magazine.begin(), m_magazine.end(), dBullet), m_magazine.end()
	);
	delete dBullet;
	m_usedBullets--;
}