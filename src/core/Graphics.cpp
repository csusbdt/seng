#include "stdafx.h"
#include "Graphics.h"
#include "Platform.h"
#include "Shader.h"
#include "Util.h"
#include "Texture.h"
#include "Matrix.h"

float Graphics::backgroundColorRed = 0;
float Graphics::backgroundColorGreen = 1;
float Graphics::backgroundColorBlue = 0;
float Graphics::backgroundColorAlpha = 1;
Shader Graphics::guiShader;
std::map<std::string, Texture *> Graphics::loadedTextures;
std::vector<Matrix *> Graphics::unusedMatrices;

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

/**
 * Render next frame of animation.
 * \todo this function is an incomplete copy of geng version
 */
void Graphics::renderNextFrame()
{
	glClearColor(backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha);
    checkOpenglError("Graphics::renderNextFrame glClearColor Failed.");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    checkOpenglError("Graphics::renderNextFrame glClear Failed.");

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

void Graphics::checkOpenglError(const std::string & msg)
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

/*
Texture * Graphics::loadTexture(const std::string & textureFilename)
{
    // If the texture is already loaded, then return point to it's texture object.
    if (loadedTextures.count(textureFilename) > 0)
    {
        return loadedTextures[textureFilename];
    }

    int numberOfFilenameCharacters = textureFilename.size() - 6;
	if (numberOfFilenameCharacters <= 0 || textureFilename.compare(numberOfFilenameCharacters, 6, ".image") != 0)
	{
		std::string msg = "Graphics::loadTexture failed.\n\n";
		msg += "Reason: Incorrect filename extension.\n\n";
		msg += "The correct extension is .image.\n\n";
		msg += "File: ";
		msg += textureFilename;
		Platform::fatalError(msg);
	}

	if (!Util::fileExists(textureFilename))
	{
		std::string msg = "Graphics::loadTexture failed.\n\n";
		msg += "Reason: File doesn't exist.\n\nFile: ";
		msg += textureFilename;
		Platform::fatalError(msg);
	}

    std::ifstream textureFile;
	textureFile.open(textureFilename.c_str(), std::ios::in | std::ios::binary);
	if (!textureFile.is_open())
    {
		std::string msg = "Graphics::loadTexture failed.\n\n";
		msg += "Reason: can not open file for reading.\n\nFile: ";
		msg += textureFilename;
		Platform::fatalError(msg);
	}

	unsigned char * bytes = NULL;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int paddedWidth = 0;
	unsigned int paddedHeight = 0;

	textureFile.read(reinterpret_cast<char *>(&width), sizeof(width));
	textureFile.read(reinterpret_cast<char *>(&height), sizeof(height));
	textureFile.read(reinterpret_cast<char *>(&paddedWidth), sizeof(paddedWidth));
	textureFile.read(reinterpret_cast<char *>(&paddedHeight), sizeof(paddedHeight));

	// for padding
	unsigned int rowPadding = paddedWidth - width;
	unsigned int numberOfBytesPerPaddedRow = paddedWidth * 4;
	unsigned int rowPaddingBytes = rowPadding * 4;
	
	unsigned int numberOfPixels = paddedWidth * paddedHeight;
    unsigned long numberOfBytes = numberOfPixels * 4;
	bytes = new unsigned char[numberOfBytes];
	
	unsigned int byteIndex = 0;
	for (unsigned int row = 0; row < height; ++row)
	{
		for (unsigned int col = 0; col < width; ++col)
		{
			// Read the 4 color components for the current pixel.
			bytes[byteIndex + 2] = textureFile.get();
			bytes[byteIndex + 1] = textureFile.get();
			bytes[byteIndex + 0] = textureFile.get();
			bytes[byteIndex + 3] = textureFile.get();
			byteIndex += 4;
		}
		byteIndex += rowPaddingBytes;
	}
	
    if (textureFile.fail())
    {
		std::string msg = "Graphics::loadTexture failed.\n\n";
		msg += "Reason: input stream failed when reading.\n\nFile: ";
		msg += textureFilename;
		Platform::fatalError(msg);
	}

	textureFile.close();

    Texture * texture = new Texture();
	texture->load(bytes, width, height, paddedWidth, paddedHeight);
	texture->activate();
	delete [] bytes;  // \todo Look at streaming bytes into GPU memory instead of reading entire block into CPU memory

    loadedTextures[textureFilename] = texture;
    return texture;
}
*/

/**
 * \brief Create a matrix.
 *
 * This class recycles matrices; if there is an unused matrix that
 * was previously created and destroyed, then return that one.
 *
 * \returns An unused matrix.
 */
Matrix * Graphics::createIdentityMatrix()
{
    if (!unusedMatrices.empty())
    {
        Matrix * matrix = unusedMatrices.back();
        unusedMatrices.pop_back();
        matrix->makeIdentity();
        return matrix;
    }
	return new Matrix();
}

void Graphics::destroyMatrix(Matrix * matrix)
{
    unusedMatrices.push_back(matrix);
}

//IndexBuffer * Graphics::createIndexBuffer(unsigned short * indices, unsigned int numberOfIndices)
//{
//}
//
//VertexBuffer * Graphics::createGuiVertexBuffer(unsigned int maxNumberOfVertices)
//{
//}
//
//VertexBuffer * Graphics::createGuiVertexBuffer(GuiVertex * vertices, unsigned int numberOfVertices)
//{
//}

void Graphics::setSceneRenderState()  
{
    /*
	glEnable(GL_DEPTH_TEST);
    checkOpenglError("GraphicsGl::setGuiRenderState glDisable Failed.");	    

    glDisable(GL_ALPHA_TEST);
    checkOpenglError("GraphicsGl::setGuiRenderState glEnable Failed.");	    

    glDisable(GL_BLEND);
    checkOpenglError("GraphicsGl::setGuiRenderState glEnable Failed.");	    
    */
}

void Graphics::setGuiRenderState()  
{
    /*
    // Turn off z-buffering.
    glDisable(GL_DEPTH_TEST);
    checkOpenglError("GraphicsGl::setGuiRenderState glDisable Failed.");	    

    // Enable alpha blending.  
    glEnable(GL_ALPHA_TEST);
    checkOpenglError("GraphicsGl::setGuiRenderState glEnable Failed.");	    

    glEnable(GL_BLEND);
    checkOpenglError("GraphicsGl::setGuiRenderState glEnable Failed.");	    

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkOpenglError("GraphicsGl::setGuiRenderState glBlendFunc Failed.");	    

    glCullFace(GL_BACK);      
    checkOpenglError("GraphicsGl::setGuiRenderState glCullFace Failed.");	    

	glEnable(GL_TEXTURE_2D);	
    checkOpenglError("GraphicsGl::setGuiRenderState glEnable Failed.");	    

    // Stencil buffer is not used in the gui.
	glDisable(GL_STENCIL_TEST); 
    checkOpenglError("GraphicsGl::setGuiRenderState glDisable Failed.");	    
    */
}
