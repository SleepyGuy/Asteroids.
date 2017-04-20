#include "EnemyShip.h"
#include <SDL2\SDL_opengl.h>
#include "Entities.h"
#include "EPhysics.h"
#include "Ship.h"
#include <algorithm>
EnemyShip::EnemyShip()
{
	GeneratePoints();
	x = -450;
	Position = Vector2D(-400, -75);
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
}

void EnemyShip::Update(float deltaTime)
{
	x += 0.015f;
	float y = 2 * (cosf(x) * (270 / PI));
	Position = Vector2D(x, y);
	
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
