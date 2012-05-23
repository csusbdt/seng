#include "stdafx.h"
#include "Platform.h"
#include "Sound.h"

Sound * Sound::load(const std::string & filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::ios::in);
	if (file.fail())
	{
		file.clear();
        Platform::fatalError("Failed to load sound file: " + filename);
	}
	file.close();
	file.clear();
    return new Sound();
}

void Sound::play()
{
}

