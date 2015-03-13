#include "stdafx.h"
#include "Platform.h"
#include "Main.h"

std::stringstream Platform::error;
unsigned int Platform::screenWidth = 300;
unsigned int Platform::screenHeight = 300;

EGLNativeWindowType Platform::eglNativeWindowType = 0;

EGLDisplay Platform::getEglDisplay()
{
    return eglGetDisplay(Main::deviceContext);
}
