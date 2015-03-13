#include "stdafx.h"
//#include "Platform.h"
#include "PlayerController.h"
#include "Thing.h"

Thing * PlayerController::thing = NULL;
double PlayerController::speed = 1;
bool PlayerController::moveRight = false;
bool PlayerController::moveLeft = false;
bool PlayerController::moveUp = false;
bool PlayerController::moveDown = false;

const double COSINE_OF_45_DEGREES = 0.70710678118L;

/**
 * If named thing already exists, a pointer to it is returned.
 */
void PlayerController::setPlayerThing(Thing * thing)
{
    PlayerController::thing = thing;
}

void PlayerController::tick(double dt)
{
    if (thing == NULL)
    {
        return;
    }

    int xdir = 0;
    if (moveRight & !moveLeft)
    {
        xdir = 1;
    }
    else if (!moveRight & moveLeft)
    {
        xdir = -1;
    }

    int ydir = 0;
    if (moveUp & !moveDown)
    {
        ydir = 1;
    }
    else if (!moveUp & moveDown)
    {
        ydir = -1;
    }

    double dist = speed * dt;
    double dx = 0;
    double dy = 0;

    if (xdir == 0 && ydir == 0)
    {
    }
    else if (xdir != 0 && ydir == 0)
    {
        dx = xdir * dist;
    }
    else if (xdir == 0 && ydir != 0)
    {
        dy = ydir * dist;
    }
    else if (xdir != 0 && ydir != 0)
    {
        dx = xdir * dist * COSINE_OF_45_DEGREES;
        dy = ydir * dist * COSINE_OF_45_DEGREES;
    }

    thing->x += dx;
    thing->y += dy;
}
