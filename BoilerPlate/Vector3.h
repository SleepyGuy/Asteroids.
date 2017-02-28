#pragma once
#ifndef _Vector_3D_H_
#define _Vector_3D_H_

namespace Engine
{
	namespace Math
	{
		class Vector3D
		{
		public:

			
			Vector3D();
			Vector3D(float x, float y, float z);
			Vector3D(float uniform);

			
			Vector3D& operator=(const Vector3D& rhs);

			float m_x;
			float m_y;
			float m_z;
		};
	}
}
#endif // !_Vector_3_H_
