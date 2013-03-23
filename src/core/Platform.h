#ifndef PROJ_PLATFORM_H
#define PROJ_PLATFORM_H

#include "stdafx.h"

/**
 * \class Platform
 *
 * \brief This class contains all platform-specific functionality that needs to 
 *        be exposed to the platform-independent core.
 *
 * Platform.h is located in the platform-independent side (under src/core). 
 * Platform.cpp is located in the platform-specific side (under platforms).
 * There is only one version of Platform.h -- as is the case for all core logic --
 * but a different version of Platform.cpp for each 
 */
class Platform
{
public:
    /**
     * \brief Width of view port.
     *
     * Excludes the window border width.
     */
    static unsigned int screenWidth;

    /**
     * \brief Height of view port.
     *
     * Excludes the window border height.
     */
    static unsigned int screenHeight;

    static void displayMessage(const std::string & msg);

    static void fatalError(const std::string & msg);

private:
};

#endif
