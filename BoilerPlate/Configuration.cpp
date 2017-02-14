#include "Configuration.hpp"

// stdlib
#include <string>
#include <fstream>
#include <sstream>
/* MOVE OUT ! */
#include <iostream>

// Engine
//
#include "Utilities.hpp"
#include "Vector2.hpp"

namespace Asteroids
{
	namespace Utilities
	{
		std::string const models_dir = "models";

		std::vector<Entities::Ship*> Configuration::LoadModels()
		{
			Engine::FileSystem::Utilities util;

			// Retrieve the files from the models directory
			//
			auto models = util.ListFiles(models_dir);

			std::vector<Entities::Ship*> ships;

			for (auto model : models)
			{
				// Load file
				//
				std::ifstream ifstream(util.BuildPath(models_dir, model));

				//
				std::string content;

				std::vector<Engine::Math::Vector2> points;
				while (ifstream >> content)
				{
					// Read components
					//
					std::stringstream lineStream(content);
					std::string cell;
					std::vector<float> components;
					while(std::getline(lineStream, cell, ','))
					{
						components.push_back(std::stof(cell));
					}

					// Add vector
					//
					points.push_back(
						Engine::Math::Vector2(components[0], components[1])
						);					
				}

				std::cout << "For model: " << model 
						  << " we read " << points.size() << " points"
					      << std::endl;

				// Adding ship to array
				//
				ships.push_back(new Asteroids::Entities::Ship(points));
			}

			return ships;
		}
	}
}