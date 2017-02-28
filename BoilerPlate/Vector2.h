#pragma once

#ifndef Vector2_H_
#define Vector2_H_

namespace Engine 
{
	namespace Math 
	{
		class Vector2D 
		{
		public:
			
			Vector2D();
			Vector2D(float uniform);
			Vector2D(float x, float y);
			Vector2D& operator=(const Vector2D& rhs);
			Vector2D& operator+=(const Vector2D& rhs);
			Vector2D& operator-=(const Vector2D& rhs);
			Vector2D& operator*=(const Vector2D& rhs);
			Vector2D& operator/=(const Vector2D& rhs);
			Vector2D operator+(const Vector2D& rhs);
			Vector2D operator-(const Vector2D& rhs);
			Vector2D operator-();
			Vector2D operator*(const Vector2D& rhs);
			Vector2D operator/(const Vector2D& rhs);
			bool operator==(const Vector2D& rhs);
			bool operator!=(const Vector2D& rhs);
			friend Vector2D operator*(float scaleUnit, const Vector2D& rhs);
			friend Vector2D operator*(const Vector2D& lhs, float scaleUnit);
			
			
			float m_x;
			float m_y;
			float m_length;
			float Length();
		};
	}
}

#endif // !Vector2_H_