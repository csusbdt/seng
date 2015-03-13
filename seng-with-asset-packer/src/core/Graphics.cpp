#include "stdafx.h"
#include "Graphics.h"
#include "Platform.h"
#include "Util.h"
#include "Thing.h"

float Graphics::backgroundColorRed = 0;
float Graphics::backgroundColorGreen = 1;
float Graphics::backgroundColorBlue = 0;
float Graphics::backgroundColorAlpha = 1;

GLuint Graphics::programObject = 0;

/**
 * Load shaders.
 *
 * \todo Load shaders.
 */
bool Graphics::init()
{
    // Load shaders.

    const char * vertexCode = 
        "attribute vec4 vPosition;    \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = vPosition;  \n"
        "}                            \n";

    const char * fragmentCode =
        "precision mediump float;                      \n"
        "void main()                                   \n"
        "{                                             \n"
        "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 ); \n"
        "}                                             \n";

    GLuint vertexShader;
    GLuint fragmentShader;

    if (!loadShader(GL_VERTEX_SHADER, vertexCode, &vertexShader))
    {
        Platform::error << "loadShader failed for vertex shader.";
        return false;
    }
    if (!loadShader(GL_FRAGMENT_SHADER, fragmentCode, &fragmentShader))
    {
        Platform::error << "loadShader failed for fragment shader.";
        return false;
    }

    programObject = glCreateProgram();
    if (!checkGlError())
    {
        Platform::error << "glCreateProgram failed.";
        return false;
    }
    if (programObject == 0)
    {
        Platform::error << "glCreateProgram returned 0.";
        return false;
    }

    glAttachShader(programObject, vertexShader);
    if (!checkGlError())
    {
        Platform::error << "glAttachShader failed.";
        return false;
    }
    glAttachShader(programObject, fragmentShader);
    if (!checkGlError())
    {
        Platform::error << "glAttachShader 2 failed.";
        return false;
    }

    glBindAttribLocation(programObject, 0, "vPosition");
    if (!checkGlError())
    {
        Platform::error << "glBindAttribLocation failed.";
        return false;
    }
    glLinkProgram(programObject);
    if (!checkGlError())
    {
        Platform::error << "glLinkProgram failed.";
        return false;
    }

    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!checkGlError())
    {
        Platform::error << "glGetProgramiv failed.";
        return false;
    }
    if (!linked) 
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (!checkGlError())
        {
            Platform::error << "glGetProgramiv 2 failed.";
            return false;
        }
        if (infoLen > 1)
        {
            char * infoLog = (char *) malloc (sizeof(char) * infoLen );
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            if (!checkGlError())
            {
                Platform::error << "glGetProgramInfoLog failed.";
                return false;
            }
            Platform::error << "Shader link error:" << std::endl << std::endl << infoLog;
            free(infoLog);
            return false;
        }
        glDeleteProgram(programObject);
        if (!checkGlError())
        {
            Platform::error << "glDeleteProgram failed.";
            return false;
        }
        return false;
    }
    return true;
}

bool Graphics::shutdown()
{
    return true;
}

bool Graphics::loadShader(GLenum shaderType, const char * shaderCode, GLuint * id)
{
    GLuint shader = glCreateShader(shaderType);
    if (!checkGlError())
    {
        Platform::error << "glCreateShader failed.";
        return false;
    }
    if (shader == 0)
    {
        Platform::error << "glCreateShader() returned 0.";
        return false;
    }

    glShaderSource(shader, 1, &shaderCode, NULL);
    if (!checkGlError())
    {
        Platform::error << "glShaderSource failed.";
        return false;
    }
   
    glCompileShader(shader);
    if (!checkGlError())
    {
        Platform::error << "glCompileShader failed.";
        return false;
    }

    // Check the compile status.
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!checkGlError())
    {
        Platform::error << "glGetShaderiv failed.";
        return false;
    }

    if (!compiled) 
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);      
        if (!checkGlError())
        {
            Platform::error << "glGetShaderiv failed.";
            return false;
        }
        if (infoLen > 1)
        {
            char * infoLog = (char *) malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            Platform::error << "Shader compilation error:\n\n" << infoLog;
            free(infoLog);
            return false;
        }
        glDeleteShader(shader);
        if (!checkGlError())
        {
            Platform::error << "glDeleteShader failed.";
            return false;
        }
        return false;
    }

    *id = shader;
    return true;
}

/**
 * Render next frame of animation.
 * \todo this function is an incomplete copy of geng version
 */
bool Graphics::renderNextFrame()
{
	glClearColor(backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha);
    if (!checkGlError())
    {
        Platform::error << "Graphics::renderNextFrame glClearColor failed.";
        return false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!checkGlError())
    {
        Platform::error << "Graphics::renderNextFrame glClear failed.";
        return false;
    }

    glViewport(0, 0, Platform::screenWidth, Platform::screenHeight);
    if (!checkGlError())
    {
        Platform::error << "Graphics::renderNextFrame glViewport failed.";
        return false;
    }
   
    Thing::drawAll();
    return true;
}

bool Graphics::checkGlError()
{
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
        Platform::error << "OpenGL ES error: " << errorCode;
        return false;
	}
    else
    {
        return true;
    }
}

//void Graphics::setBackgroundImage(const std::string & fileName, unsigned int width, unsigned int height)
//{
//    if (fileName == backgroundFileName)
//    {
//        return;
//    }
//    if (fileName.size() == 0)
//    {
//        // clear texture.
//        assert(false);
//    }
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
//    checkGlError("glBindTexture");
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei) width, (GLsizei) height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
//}
