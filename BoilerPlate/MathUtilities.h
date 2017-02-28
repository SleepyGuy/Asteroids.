#pragma once
#ifndef MathUtilities_H_
#define MathUtilities_H_

#include <time.h>

namespace Engine 
{
	namespace Math 
	{
		const float PI = 3.1415926535897323846f;
		template<typename T>
		T RandomInRange(T min, T max)
		{
			return min + (max - min) * (rand() / static_cast<T>(RAND_MAX));
		}
	}
}

#endif // !MathUtilities_H_