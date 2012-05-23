#ifndef PROJ_PLATFORM_H
#define PROJ_PLATFORM_H

#include "stdafx.h"

/**
 * \class Platform
 *
 * \brief Application facing interface to platform-specific resources.
 *
 * Platform.h is located under src/core; platform-specific versions of 
 * Platform.cpp are located under platforms/*. 
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

    /**
     * Swap display buffers.
     */
    static void swapBuffers();
        
    static void displayMessage(const std::wstring & msg);

    static void displayMessage(const std::string & msg);

    static void fatalError(const std::wstring & msg);

    static void fatalError(const std::string & msg);

private:
};

#endif
