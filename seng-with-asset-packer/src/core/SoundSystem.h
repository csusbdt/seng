#ifndef SENG_SOUND_SYSTEM_H
#define SENG_SOUND_SYSTEM_H

#include "stdafx.h"

class Thing;

/**
 * \class PlayerController
 *
 * \brief Player controller logic.
 *
 * User input events are sent here.
 *
 * 
 */
class SoundSystem
{
public:		
    static void tick(double dt);

private:
    SoundSystem() { assert(false); }
};

#endif