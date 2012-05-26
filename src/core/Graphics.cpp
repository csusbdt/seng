#include "stdafx.h"
#include "Graphics.h"
#include "Platform.h"
#include "Util.h"
#include "Thing.h"

float Graphics::backgroundColorRed = 0;
float Graphics::backgroundColorGreen = 1;
float Graphics::backgroundColorBlue = 0;
float Graphics::backgroundColorAlpha = 1;

EGLint Graphics::frameBufferAttributes[] = { 
    EGL_RED_SIZE, 4,
    EGL_GREEN_SIZE, 4,
    EGL_BLUE_SIZE, 4,
    EGL_ALPHA_SIZE, 0,
    EGL_DEPTH_SIZE, 8,
    EGL_NONE 
};
EGLConfig Graphics::frameBufferConfiguration;
EGLint Graphics::numFrameBufferConfigurations = 0;
EGLDisplay Graphics::eglDisplay = EGL_NO_DISPLAY;
EGLSurface Graphics::eglSurface = EGL_NO_SURFACE;
EGLContext Graphics::eglContext = EGL_NO_CONTEXT;
GLuint Graphics::programObject = 0;

void Graphics::checkEglError(const std::string & msg)
{
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
    {
        std::stringstream ss;
        ss << msg << "\nEGL error code: " << error << std::endl;
        Platform::fatalError(ss.str());
    }
}

/**
 * Load shaders.
 *
 * \todo Load shaders.
 */
void Graphics::init()
{
    // Get the display handle.
    eglDisplay = Platform::getEglDisplay();
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        Platform::fatalError("No EGL Display.");
    }

    // Check OpenGL ES version.    
    EGLint major;
    EGLint minor;
    eglInitialize(eglDisplay, &major, &minor);
    checkEglError("eglInitialize");
    if (major == 1 && minor < 4)
    {
        Platform::fatalError("EGL version 1.4 or later required.");
        return;
    }

    memset(&frameBufferConfiguration, 0, sizeof(EGLConfig));  // Not sure this is needed.
    eglChooseConfig(eglDisplay, frameBufferAttributes, &frameBufferConfiguration, 1, &numFrameBufferConfigurations);
    checkEglError("Call to eglChooseConfig failed.");
    if (numFrameBufferConfigurations == 0)
    {
        Platform::fatalError("No EGL frame buffer configurations that match the specified requirements.");
    }

    // Create a window surface.
    EGLint surfaceAttributes[] = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER, EGL_NONE, EGL_NONE };
    eglSurface = eglCreateWindowSurface(eglDisplay, frameBufferConfiguration, Platform::eglNativeWindowType, surfaceAttributes);
    checkEglError("eglCreateWindowSurface");
    if (eglSurface == EGL_NO_SURFACE)
    {
        Platform::fatalError("Call to eglCreateWindowSurface failed.");
    }

    createContext();

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
    checkEglError("glCreateProgram");
    if (programObject == 0)
    {
        Platform::fatalError("glCreateProgram returned 0.");
        return;
    }

    glAttachShader(programObject, vertexShader);
    checkEglError("glAttachShader");
    glAttachShader(programObject, fragmentShader);
    checkEglError("glAttachShader 2");

    glBindAttribLocation(programObject, 0, "vPosition");
    checkEglError("glBindAttribLocation");
    glLinkProgram(programObject);
    checkEglError("glLinkProgram");

    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    checkEglError("glGetProgramiv");
    if (!linked) 
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        checkEglError("glGetProgramiv");
        if (infoLen > 1)
        {
            char * infoLog = (char *) malloc (sizeof(char) * infoLen );
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            checkEglError("glGetProgramiv");
            std::stringstream ss;
            ss << "Shader link error: \n\n" << infoLog;
            Platform::fatalError(ss.str()); 
            free(infoLog);
        }
        glDeleteProgram(programObject);
        checkEglError("glDeleteProgram");
        return;
    } 
}

/**
 * \brief Create a new context and make it current.
 *
 * This function is called at program start up and after power events.
 */
void Graphics::createContext()
{  
    assert(eglContext == EGL_NO_CONTEXT);
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, frameBufferConfiguration, EGL_NO_CONTEXT, contextAttributes);
    checkEglError("eglCreateContext");
    if (eglContext == EGL_NO_CONTEXT)
    {   
        Platform::fatalError("eglCreateContext returned EGL_NO_CONTEXT");
    }
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    checkEglError("eglMakeCurrent");
}

/**
 * \brief Destroy the context.
 *
 * This function is called after power events and at shutdown.
 */
void Graphics::destroyContext()
{
    assert(eglContext != EGL_NO_CONTEXT);

    // Make sure the context is not current.
    if (eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
    {
        EGLint error = eglGetError();
        if (error == EGL_CONTEXT_LOST)
        {
            Platform::displayMessage("Power event when trying to initialize.  I don't know how to handle this.");
            return;
        }
        Platform::fatalError("eglMakeCurrent failed in Graphics::initializeOpenglState.  Maybe this is normal when power events occur.");
        return;
    }

    // Destroy the context.
    eglDestroyContext(eglDisplay, eglContext);
    checkEglError("eglDestroyContext");
    eglContext = EGL_NO_CONTEXT;
}

void Graphics::shutdown()
{
    destroyContext();
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);
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

    if (EGL_FALSE == eglSwapBuffers(eglDisplay, eglSurface))
    {
        // eglSwapBuffers will fail after a power event.
        // In this case, we need to reinitialize.
        EGLint error = eglGetError();	
        if (error == EGL_CONTEXT_LOST)
        {
            // Power event; need to "... destroy all contexts and reinitialise OpenGL ES state 
            // and objects to continue rendering." 
            destroyContext();
            createContext();
        }
    }
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
