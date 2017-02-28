#include "Vector3.h"

namespace Engine 
{
	namespace Math 
	{
		Vector3D::Vector3D()
			: m_x(0.f)
			, m_y(0.f)
			, m_z(0.f)
		{};
		Vector3D::Vector3D(float x, float y, float z) 
			: m_x(x)
			, m_y(y)
			, m_z(z)
		{};
		Vector3D::Vector3D(float uniform) 
			: m_x(uniform)
			, m_y(uniform)
			, m_z(uniform)
		{};

		Vector3D& Vector3D::operator=(const Vector3D& rhs) 
		{
			if (this == &rhs)
			{
				return *this;
			}

			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;

			return *this;
		};
	}
}