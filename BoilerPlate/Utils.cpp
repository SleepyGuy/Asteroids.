#include "Utils.h"

// stdlib
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Engine
#include "Utilities.h"
#include "Vector2.h"

namespace Asteroids
{
	namespace Utilities
	{

		std::string const folder_name = "models";

		//Load models
		std::vector<Entity::Ship*> Load::LoadModels()
		{
			Engine::FileSystem::Utilities util;
			auto modelsList = util.ListFile(folder_name);

			std::vector<Entity::Ship*> ships;

			std::cout << " Loading Models " << std::endl;
			for (int i = 2; i < modelsList.size(); i++)
			{
				std::string model = modelsList[i];
				std::ifstream inFile(util.buildPath(folder_name, model));
				std::string current("");
				std::vector<Engine::Math::Vector2D> points;

				if (inFile.good())
				{
					std::string getFloat;
					while (inFile >> current)
					{
						std::vector<float> pointsRead;
						getFloat = current.substr(0, current.find_last_of(","));
						pointsRead.push_back(std::stof(getFloat));
						getFloat = current.substr(current.find_last_of(",") + 1, current.length());
						pointsRead.push_back(std::stof(getFloat));
						points.push_back(Engine::Math::Vector2D(pointsRead[0], pointsRead[1]));
					}
				}

				std::cout << model << " has " << points.size() << " points" << std::endl;
				
				Entity::Ship* temp = new Entity::Ship(points);

				ships.push_back(temp);
			}
			std::cout << std::endl;
			return ships;
		}
	}
}