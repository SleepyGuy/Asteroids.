#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.hpp"
#include "Drawable2D.hpp"
namespace Asteroids
{
	namespace Entities
	{
		class Entity : public Engine::Graphics::Drawable2D
		{
		public:
			
		protected:
			float m_angleinRads;
		};
	}
}

#endif // !_ENTITY_H_
