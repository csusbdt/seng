#ifndef PROJ_UTIL_H
#define PROJ_UTIL_H

#include "stdafx.h"

class Util
{
public:
	static bool fileExists(const std::string & filename);
		
private:
	Util() { assert(false); }
};

#endif