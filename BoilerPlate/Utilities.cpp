#include "Utilities.hpp"

#include <Windows.h>	
#include <sstream>



namespace Engine 
{
	namespace FileSystem 
		{
		std::string Utilities::GetExeFileName() {
			wchar_t buff[MAX_PATH];
			GetModuleFileName(NULL, buff, MAX_PATH);
			std::wstring w_buff(buff);
			return std::string(w_buff.begin(), w_buff.end());
		}
		std::string Utilities::GetPathExe() {
			std::string f = GetExeFileName();
			return f.substr(0, f.find_last_of("\\/"));
		}

		std::string Utilities::GetLocalPathExpr(std::string dir) {
			std::string current = GetPathExe() + "\\" + dir;
			std::wstring s(current.begin(), current.end());
			std::wstring file = s + L"\\*.*";
			return std::string(file.begin(), file.end());
		}

		std::string Utilities::GetLocalPathExpr(std::string dir, std::string wildcard)
		{
			std::string current = GetPathExe() + "\\" + dir + "\\" + wildcard;
			return current;
		}

		std::string Utilities::BuildPath(std::string prefix, std::string sufix)
		{
			std::stringstream path;

			path << prefix;
			path << "\\";
			path << sufix;

			return path.str();
		}

		std::vector<std::string> Utilities::ListFiles(std::string dir, std::string wildcard) {
			//PATH
			std::string path = GetLocalPathExpr(dir, wildcard);

			//Transforming
			std::wstring w_path(path.begin(), path.end());

			WIN32_FIND_DATA ffd;

			std::vector<std::string> vs;
			HANDLE hFind;
			hFind = FindFirstFile(w_path.c_str(), &ffd);
			if (hFind != INVALID_HANDLE_VALUE) {
				do {
					std::wstring fname(ffd.cFileName);
					if (fname == L"." || fname == L"..")
						continue;
					vs.push_back(
						std::string(fname.begin(), fname.end())
					);
				} while (FindNextFile(hFind, &ffd));
				FindClose(hFind);
			}

			return vs;
		}
		
	}
}