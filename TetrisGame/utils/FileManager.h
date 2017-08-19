#pragma once
#include <string>
#include <fstream>

class FileManager
{
public:
	FileManager();
	~FileManager();

	static bool IsFileExists(std::string const& filepath);
};

