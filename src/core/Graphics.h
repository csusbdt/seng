#ifndef PROJ_GRAPHICS_H
#define PROJ_GRAPHICS_H

#include "stdafx.h"

/**
 * \class Graphics
 * 
 * \brief Container of top-level graphics functionality.
 *
 * \todo Need way to destroy textures and reset graphics memory.
 */
class Graphics
{
public:
    static float backgroundColorRed;
	static float backgroundColorGreen;
	static float backgroundColorBlue;
	static float backgroundColorAlpha;
    static GLuint programObject;

    static void init(); 
    static void shutdown(); 
    static void renderNextFrame();
    static void checkGlError(const std::string & msg);

private:
    static void setSceneRenderState();
    static void setGuiRenderState();

    static GLuint loadShader(GLenum shaderType, const char * shaderCode);
};

#endif
