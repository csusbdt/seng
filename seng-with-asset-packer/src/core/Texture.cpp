#include "stdafx.h"

#include "Platform.h"
#include "Texture.h"
#include "Graphics.h"

bool Texture::load(unsigned char * data, unsigned int width, unsigned int height, unsigned int paddedWidth, unsigned int paddedHeight, bool generateMipmap)
{
	this->width = width;
	this->height = height;
	this->paddedWidth = paddedWidth;
	this->paddedHeight = paddedHeight;
	maxU = width / static_cast<float>(paddedWidth);
	maxV = height / static_cast<float>(paddedHeight);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glPixelStorei failed.";
        return false;
    }

	glGenTextures(1, &openGlTexture);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glGenTextures failed.";
        return false;
    }

	glBindTexture(GL_TEXTURE_2D, openGlTexture);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glBindTexture failed.";
        return false;
    }

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glTexParameterf failed.";
        return false;
    }

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glTexParameterf failed.";
        return false;
    }

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glTexImage2D failed.";
        return false;
    }

    mipmap = generateMipmap;
    if (mipmap)
    {
	    //gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	    glGenerateMipmap(GL_TEXTURE_2D);
        if (!Graphics::checkGlError())
        {
            Platform::error << "glGenerateMipmap failed.";
            return false;
        }
    }

    return true;
}

bool Texture::activate()
{
	glBindTexture(GL_TEXTURE_2D, openGlTexture);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glBindTexture failed.";
        return false;
    }

    if (tile)
    {
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        if (!Graphics::checkGlError())
        {
            Platform::error << "glTexParameterf failed.";
            return false;
        }

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        if (!Graphics::checkGlError())
        {
            Platform::error << "glTexParameterf failed.";
            return false;
        }
    }
    return true;
}

bool Texture::deactivate()
{
	glBindTexture(GL_TEXTURE_2D, 0);
    if (!Graphics::checkGlError())
    {
        Platform::error << "glBindTexture failed.";
        return false;
    }
    else
    {
        return true;
    }
}
