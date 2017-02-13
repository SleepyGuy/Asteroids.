#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <vector>

std::string GetExeFileName() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring w_buff(buffer);
	return std::string(w_buff.begin(), w_buff.end());
}

std::string GetExePath() {
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

std::string GetLocalPathExpr(std::string dir) {
	std::string current = GetExePath() + "\\" + dir;
	std::wstring s(current.begin(), current.end());
	std::wstring file = s + L"\\*.*";
	return std::string(file.begin(), file.end());
}

std::vector<std::string> ListFiles(std::string dir) {
	//Transform

	std::wstring w_path(dir.begin(), dir.end());

	WIN32_FIND_DATA FindFileData;
	std::vector<std::string> vs;
	HANDLE hFind;
	hFind = FindFirstFile(w_path.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::wstring fname(FindFileData.cFileName);
			vs.push_back(
				std::string(fname.begin(), fname.end())
			);
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return vs;
}

int main() {

	std::cout << GetExeFileName() << std::endl;
	std::cout << GetExePath() << std::endl;
	std::cout << GetLocalPathExpr("models") << std::endl;
	std::vector<std::string> vs = ListFiles(GetLocalPathExpr("models"));
	std::cout << vs.size() << std::endl;

	std::cout << "count: " << vs.size() << "\n";
	for (auto item : vs)
		std::cout << item << "\n";
	std::cout << std::endl;

	//Printing enterprise.points
	std::cout << "enterprise.points contents\n\n";
	std::ifstream f("enterprise.points");

	if (f.is_open())
		std::cout << f.rdbuf() << std::endl;
	std::cout << "\n";

	//Printing falcon.points
	std::cout << "falcon.points contents\n\n";
	std::ifstream g("falcon.points");

	if (g.is_open())
		std::cout << g.rdbuf() << std::endl;
	std::cout << "\n";

	//Printing ship.points
	std::cout << "ship.points contents\n\n";
	std::ifstream h("ship.points");

	if (h.is_open())
		std::cout << h.rdbuf() << std::endl;
	std::cout << "\n";

	return 0;


}