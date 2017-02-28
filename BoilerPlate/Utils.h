#pragma once

#ifndef Utils_H_
#define Utils_H_

//STD includes
#include <vector>

//Game includes
#include "Ship.h"

namespace Asteroids 
{
	namespace Utilities 
	{
		class Load
		{
			public:

				std::vector<Entity::Ship*> LoadModels();
		};
	}
}
#endif // !Utils_H_