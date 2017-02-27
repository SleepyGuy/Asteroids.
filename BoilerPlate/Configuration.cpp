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
#include "Constants.hpp"
#include "MathUtilities.hpp"

namespace Asteroids
{
	namespace Utilities
	{
		std::string const models_dir = "models";

		std::vector<Entities::Ship*> Configuration::LoadModels()
		{
			Engine::FileSystem::Utilities util;

			// Get files from models 
			auto models = util.ListFiles(models_dir);

			std::vector<Entities::Ship*> ships;

			for (auto model : models)

			{
				
				std::ifstream ifstream(util.BuildPath(models_dir, model));

			
				std::string content;

				std::vector<Engine::Math::Vector2> points;
				while (ifstream >> content)
				{
					
					std::stringstream lineStream(content);
					std::string cell;
					std::vector<float> components;
					while (std::getline(lineStream, cell, ','))
					{
						components.push_back(std::stof(cell));
					}

					points.push_back(
						Engine::Math::Vector2(components[0], components[1])
					);
				}

				std::cout << "For " << model
					<< " there are " << points.size() << " points"
					<< std::endl;

				// Adding ship to array
				ships.push_back(new Asteroids::Entities::Ship(points));
			}

			return ships;
		}

		const int NUM_POINTS = 16;
		const float MIN_SIZE = 25.0f;
		const float MAX_SIZE = 45.0f;
		const float ROTATION_SPEED = 120.0f;
		//Drawing an asteroid
		std::vector<Entities::Asteroid*> Configuration::CreateAsteroid(int totalasteroid)
		{
			std::vector<Entities::Asteroid*> asteroid;
			std::vector<Engine::Math::Vector2> ast_points;

			float min = MIN_SIZE / m_sizeFactor;
			float max = MAX_SIZE / m_sizeFactor;

			// Random generation 

			for (int i = 0; i < totalasteroid; i++)
			{
				for (int idx = 0; idx < NUM_POINTS; ++idx)
				{
					const float radians = (idx / static_cast<float>(NUM_POINTS)) * 2.0f * Engine::Math::PI;
					const float randDist = Engine::Math::RandomInRange<float>(min, max);

					ast_points.push_back(Engine::Math::Vector2(sinf(radians) * randDist, cosf(radians) * randDist));
				}

				std::cout << "There are " << ast_points.size() << " points"
					<< std::endl;

				asteroid.push_back(new Asteroids::Entities::Asteroid(ast_points));
			}
			std::cout << "Asteroids: " << asteroid.size() << std::endl;
				return asteroid;
			
		}
	}
}