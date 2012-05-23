#include "stdafx.h"
#include "Util.h"

bool Util::fileExists(const std::string & filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::ios::in);
	if (file.fail())
	{
		file.clear();
		return false;
	}
	file.close();
	file.clear();
	return true;
}

