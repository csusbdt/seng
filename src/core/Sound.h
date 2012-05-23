#ifndef PROJ_SOUND_H
#define PROJ_SOUND_H

#include "stdafx.h"

/**
 * \class Sound
 *
 * \brief Memory-resident sound data.
 *
 * Sound data can be generated procedurally or loaded from a file
 * using this class's load function.
 *
 * We need to work out the details of how sound data is passed to 
 * platform logic.
 */
class Sound
{
public:
	static Sound * load(const std::string & filename);
    void play();
		
private:
	Sound() { }
};

#endif