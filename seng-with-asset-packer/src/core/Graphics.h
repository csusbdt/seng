#ifndef PROJ_GRAPHICS_H
#define PROJ_GRAPHICS_H

#include "stdafx.h"

/**
 * \class Graphics
 * 
 * \brief Container of top-level graphics functionality.
 *
 * See http://www.khronos.org/opengles/sdk/docs/man/
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
    static std::string backgroundFileName;

    static GLuint programObject;

    static bool init(); 
    static bool shutdown(); 
    static bool renderNextFrame();
    static bool checkGlError();
    static bool setBackgroundImage(const std::string & fileName);

private:
    static bool setSceneRenderState();
    static bool setGuiRenderState();
    static bool loadShader(GLenum shaderType, const char * shaderCode, GLuint * id);
};

#endif
