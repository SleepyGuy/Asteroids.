#include "Ship.h"
#include "SDL2\SDL_opengl.h"
#include <cmath>
#include <algorithm>
#include "EPhysics.h"


namespace Asteroids
{
	namespace Entity
	{
		int m_lives = 10;
		Ship::Ship(std::vector<Engine::Math::Vector2D> model_points)
			: m_velocity()
			, m_usedBullets(0)
		{
			m_points = model_points;
			m_radius = 40.f;
			m_angle = 0.f;
			m_angleInRads = 0.f;
			Mass();
			m_respawnTime = 0;
			m_currentSpeed = 0.f;
		};

		void Ship::Render()
		{
			// Respawn delay
			if (!m_inmune) 
			{
				if (m_respawnTime >= 120)
				{
					setCollision(true);
					m_respawnTime = 0;
					m_currentColor = Engine::Math::Vector3D(1.f);
				}
				m_respawnTime++;
			}

			
			glLoadIdentity();

			wrapAround();

			
			glTranslatef(m_position.m_x, m_position.m_y, 0.0f);

			glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

			glColor3f(1, 1, 1);

			glBegin(GL_LINE_LOOP);
			for (auto temp : m_points)
			{
				glVertex2f(temp.m_x, temp.m_y);
			}
			glEnd();

			m_angleInRads = (m_angle + Asteroids::angle_offset) * (Engine::Math::PI / 180);

			for (int i = 0; i < m_magazine.size(); i++)
				m_magazine[i]->Render();


			return;
		}
		void Ship::RenderLives(unsigned int mode, std::vector<Engine::Math::Vector2D> points, int factor)
		{
			glLoadIdentity();
			glTranslatef(260.0f - (factor * 60), 300.0f, 0.0f);
			glBegin(mode);
			for (auto point : points)
			{
				glVertex2f(point.GetX(), point.GetY());
			}
			glEnd();
		}
		void Ship::DrawLives(int lives)
		{
			Entity::Ship::translate(m_position);
			for (int i = 0; i<lives; i++)
				 Entity::Ship::RenderLives(GL_LINE_LOOP, m_points, i);
		}

		void Ship::MoveForward()
		{
			
			if (m_mass > 0)
			{
				float impulse = (Physics::THRUST / m_mass);
				float x = impulse * std::cosf(m_angleInRads);
				float y = impulse * std::sinf(m_angleInRads);

				m_velocity += Engine::Math::Vector2D(x, y);
			}
		}

		void Ship::MoveRight()
		{
			rotate(-5.0f);
		}

		void Ship::MoveLeft()
		{
			rotate(5.0f);
		}

		void Ship::Shoot()
		{
			if (m_usedBullets == 5) return;
			else if (m_usedBullets < 5)
			{
				Bullet* nBullet = new Bullet(m_position, m_velocity, m_angle);
				m_magazine.push_back(nBullet);
				m_usedBullets++;
			}
		}

		void Ship::translate(Engine::Math::Vector2D pos) 
		{
			
			m_position = pos;
		};

		void Ship::rotate(float num) 
		{
			
			m_angle += num;
			m_angleInRads = (m_angle + Asteroids::angle_offset) * (Engine::Math::PI / 180);
		};

		void Ship::Update(float deltaTime) 
		{
			
			float speed = std::fabs(m_velocity.Length());
			if (speed > Physics::MAX_PLAYER_SPEED)
			{
				m_velocity = Engine::Math::Vector2D(
				(m_velocity.m_x / speed) * Physics::MAX_PLAYER_SPEED,
				(m_velocity.m_y / speed) * Physics::MAX_PLAYER_SPEED
				 );

				m_currentSpeed = std::fabs(m_velocity.m_length);
			}
			
			
			m_velocity = Engine::Math::Vector2D(
				m_velocity.m_x * Physics::DRAG, 
				m_velocity.m_y * Physics::DRAG);

			
			Engine::Math::Vector2D pos = m_position + m_velocity;

			
			translate(pos);

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

		void Ship::Respawn() 
		{
			setCollision(false);
			m_position = Engine::Math::Vector2D(0.f);
			ResetOrientation();
			m_currentColor = Engine::Math::Vector3D(1.f, 0.f, 0.f);
			setVelocity(Engine::Math::Vector2D(0.f, 0.f));
		};

		void Ship::wrapAround() 
		{
			if (m_position.m_x > 650)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
			else if (m_position.m_x < -650)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}

			if (m_position.m_y > 400)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
			else if (m_position.m_y < -400)
			{
				Engine::Math::Vector2D invertedPos(m_position.m_x * -1, m_position.m_y * -1);
				translate(invertedPos);
			}
		};

		void Ship::deleteBullet(Bullet* dBullet) 
		{
			m_magazine.erase(
				remove(m_magazine.begin(), m_magazine.end(), dBullet), m_magazine.end()
			);
			delete dBullet;
			m_usedBullets--;
		}

		void Ship::Mass() 
		{
			for(auto count : m_points) 
			{
				m_mass += 0.2f;
			}

			if (m_mass < 1.0f)
				m_mass = 1.5f;

			return;
		};

		void Ship::ResetOrientation() 
		{
			m_angle = 0.f;
			m_angleInRads = 0.f;
		};
	}
}