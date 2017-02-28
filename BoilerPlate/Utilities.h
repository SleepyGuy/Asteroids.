#pragma once

#ifndef Utilities_H
#define Utilities_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

namespace Engine
{
	namespace FileSystem
	{
		class Utilities
		{
			public:
	
				std::vector<std::string> ListFile(std::string file);
		
				void printUtil(std::vector<std::string> list);
				
				std::string buildPath(std::string pre, std::string pos);

			protected:
				std::vector<std::string> list_of_files;
				std::string getPath(std::string file);
				void printFileContent(std::string fileName);
		};
	}
}
#endif //Utilities_H