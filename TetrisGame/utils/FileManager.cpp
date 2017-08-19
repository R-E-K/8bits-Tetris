#include "FileManager.h"



FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

bool FileManager::IsFileExists(std::string const& filepath)
{
	std::ifstream ifile(filepath);
	return (ifile.good());
}
