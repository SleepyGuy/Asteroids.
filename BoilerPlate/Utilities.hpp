#pragma once
#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <string>
#include <vector>
namespace Engine
{
	namespace FileSystem
	{
		class Utilities
		{
		public:
		
			std::string BuildPath(std::string prefix, std::string suffix);
			std::vector<std::string> ListFiles(std::string dir, std::string wildcard = "*.*");
		private:
			std::string GetExeFileName();
			std::string GetPathExe();
			std::string GetLocalPathExpr(std::string dir);
			std::string GetLocalPathExpr(std::string dir, std::string wildcard);
		};
	}
}
#endif