#ifndef PROJ_GRAPHICS_H
#define PROJ_GRAPHICS_H

#include "stdafx.h"

class Shader;
class Matrix;
class Texture;
//class IndexBuffer;
//class VertexBuffer;
//class GuiVertex;

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

    /**
     *
     */
    static void init(); 
    static void shutdown(); 
    static void renderNextFrame();
    static void checkOpenglError(const std::string & msg);

    /**
     * Load texture data from file system and store into GPU memory.
     * In case texture is already loaded, returns pointer to already loaded texture.
     * 
     * \param textureFilename Can include path prefix; must exclude .image extension.
     * \returns pointer to loaded texture.
     */
	static Texture * loadTexture(const std::string & textureFilename);

	static Matrix * createIdentityMatrix();
	static void destroyMatrix(Matrix * matrix);
//	static IndexBuffer * createIndexBuffer(unsigned short * indices, unsigned int numberOfIndices);
//	static VertexBuffer * createGuiVertexBuffer(unsigned int maxNumberOfVertices);
//	static VertexBuffer * createGuiVertexBuffer(GuiVertex * vertices, unsigned int numberOfVertices);

private:
    static EGLint frameBufferAttributes[];
    static EGLConfig frameBufferConfiguration;
    static EGLint numFrameBufferConfigurations;

    static EGLDisplay eglDisplay;
    static EGLSurface eglSurface;
    static EGLContext eglContext;

    static Shader guiShader;
    static std::map<std::string, Texture *> loadedTextures;
    static std::vector<Matrix *> unusedMatrices;

    static void checkEglError(const std::string & msg);
    static void createContext();
    static void destroyContext();

    static void setSceneRenderState();
    static void setGuiRenderState();
};

#endif
