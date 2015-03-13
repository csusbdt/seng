#ifndef SENG_PLAYER_CONTROLLER_H
#define SENG_PLAYER_CONTROLLER_H

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
class PlayerController
{
public:
    static double speed;

    static bool moveRight;
    static bool moveLeft;
    static bool moveUp;
    static bool moveDown;
		
    /**
     * Because name is used as a map key, user code should not be able to modify it.
     */
	static void setPlayerThing(Thing * thing);
    static void tick(double dt);

private:
    static Thing * thing;

    PlayerController() { assert(false); }
};

#endif