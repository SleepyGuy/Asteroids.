#include "Drawable2D.hpp"
// OPENGL
#include <SDL2\SDL_opengl.h>

namespace Engine
{
	namespace Graphics
	{
		void Drawable2D::Translate(Math::Vector2 position)
		{
			m_position = position;
		}

		void Drawable2D::Draw(unsigned int mode, std::vector<Math::Vector2> points)
		{
			// Reset transformation matrix to identity
			//
			glLoadIdentity();

			// Translate
			//
			glTranslatef(m_position.GetX(), m_position.GetY(), 0.0f);

			// Draw
			//
			glBegin(mode);
				for(auto point : points)
				{
					glVertex2f(point.GetX(), point.GetY());
				}				
			glEnd();
		}
	}
}