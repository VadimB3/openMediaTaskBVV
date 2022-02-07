#pragma once
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;
class FileComparison {
public:
	void Directory_iterator();
private:
	bool Files_to_cmp(const std::string& file_path1, const std::string& file_path2);
};