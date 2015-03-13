#ifndef PROJ_PLATFORM_H
#define PROJ_PLATFORM_H

#include "stdafx.h"

/**
 * \class Platform
 *
 * \brief Application facing interface to platform-specific resources.
 *
 * Platform.h is located under src/core; platform-specific versions of 
 * Platform.cpp are located under platforms. 
 */
class Platform
{
public:
    /**
     * \brief Error message to be printed on exit.
     *
     * When this stream contains characters it means there has been an error 
     * and that the system should be shutting down.
     */
    static std::stringstream error;

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

    static EGLNativeWindowType eglNativeWindowType;

    static EGLDisplay getEglDisplay();

private:
};

#endif
