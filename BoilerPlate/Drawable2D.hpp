#pragma once
#ifndef _DRAWABLE2D_H_
#define _DRAWABLE2D_H_
#include <iostream>
// STDLIB
#include <vector>

// ENGINE
#include "Vector2.hpp"

namespace Engine
{
	namespace Graphics
	{
		const float ANGLE_OFFSET = 90.0f;
		class Drawable2D
		{
		public:
			
			virtual void Translate(Engine::Math::Vector2 pos);
			virtual void Draw(unsigned int mode, std::vector<Math::Vector2> points);
		    virtual void Tranzwarp();
			virtual void rotate(float num);
		protected:
			
			Engine::Math::Vector2 m_ShipPosition;
			float m_angle = 0.0f;
			float m_angleInRads = 0.0f;
			float m_PlayerSpeed = 5.0f;
		};
	}
}



#endif // !_DRAWABLE_H_
