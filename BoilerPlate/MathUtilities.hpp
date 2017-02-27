#pragma once
#ifndef _MATHUTILITIES_H_
#define _MATHUTILITIES_H_

#include <cstdlib>

namespace Engine
{
	namespace Math
	{
		template <typename T>
		T RandomInRange(T min, T max)
		{
			return min + (max - min) * (rand() / static_cast<T>(RAND_MAX+1.0f));
		}
	}
}

#endif // !_MATHUTILITIES_H_
