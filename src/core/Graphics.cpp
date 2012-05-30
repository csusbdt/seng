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
void Graphics::init()
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

    vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode);
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode);

    programObject = glCreateProgram();
    checkGlError("glCreateProgram");
    if (programObject == 0)
    {
        Platform::fatalError("glCreateProgram returned 0.");
        return;
    }

    glAttachShader(programObject, vertexShader);
    checkGlError("glAttachShader");
    glAttachShader(programObject, fragmentShader);
    checkGlError("glAttachShader 2");

    glBindAttribLocation(programObject, 0, "vPosition");
    checkGlError("glBindAttribLocation");
    glLinkProgram(programObject);
    checkGlError("glLinkProgram");

    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    checkGlError("glGetProgramiv");
    if (!linked) 
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        checkGlError("glGetProgramiv");
        if (infoLen > 1)
        {
            char * infoLog = (char *) malloc (sizeof(char) * infoLen );
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            checkGlError("glGetProgramiv");
            std::stringstream ss;
            ss << "Shader link error: \n\n" << infoLog;
            Platform::fatalError(ss.str()); 
            free(infoLog);
        }
        glDeleteProgram(programObject);
        checkGlError("glDeleteProgram");
        return;
    } 
}

void Graphics::shutdown()
{
}

GLuint Graphics::loadShader(GLenum shaderType, const char * shaderCode)
{
   GLuint shader = glCreateShader(shaderType);
   checkGlError("glCreateShader");
   if (shader == 0)
   {
       Platform::fatalError("glCreateShader() returned 0.");
       return 0;
   }

   glShaderSource(shader, 1, &shaderCode, NULL);
   checkGlError("glShaderSource");
   
   glCompileShader(shader);
   checkGlError("glCompileShader");

   // Check the compile status.
   GLint compiled;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
   checkGlError("glGetShaderiv");

   if (!compiled) 
   {
      GLint infoLen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);      
      checkGlError("glGetShaderiv");
      if (infoLen > 1)
      {
         char * infoLog = (char *) malloc(sizeof(char) * infoLen);
         glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
         std::stringstream ss;
         ss << "Shader comilation error:\n\n" << infoLog;
         Platform::fatalError(ss.str());
         free(infoLog);
      }
      glDeleteShader(shader);
      checkGlError("glDeleteShader");
      return 0;
   }

   return shader;
}

/**
 * Render next frame of animation.
 * \todo this function is an incomplete copy of geng version
 */
void Graphics::renderNextFrame()
{
	glClearColor(backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha);
    checkGlError("Graphics::renderNextFrame glClearColor Failed.");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkGlError("Graphics::renderNextFrame glClear Failed.");

    glViewport(0, 0, Platform::screenWidth, Platform::screenHeight);
    checkGlError("glViewport");
   
    Thing::drawAll();
}

void Graphics::checkGlError(const std::string & msg)
{
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
		std::stringstream ss;
		ss << "OpenGL ES error: " << errorCode << std::endl << std::endl;
		ss << msg << std::endl << std::endl;
		Platform::fatalError(ss.str());
	}
}
