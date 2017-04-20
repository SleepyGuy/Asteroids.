#include "EnemyShip.h"
#include <SDL2\SDL_opengl.h>
#include "Entities.h"
EnemyShip::EnemyShip()
{
	GeneratePoints();
}

void EnemyShip::Render()
{
	glLoadIdentity();

	
	glTranslatef(-450, -75, 0.0f);

	glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

	glColor3f(3, 0, 1);

	glBegin(GL_LINE_LOOP);
	for (auto temp : m_points)
	{
		glVertex2f(temp.m_x, temp.m_y);
	}
	glEnd();
}

void EnemyShip::Update(float deltaTime)
{
	Engine::Math::Vector2D current;
	if (m_mass > 0)
	{
		float impulse = (2.0f / m_mass);
		float x = impulse * std::cosf(180);
		float y = impulse * std::sinf(90);

		current += Engine::Math::Vector2D(x, y);
	}
	current += m_position;
	translate(current);
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
