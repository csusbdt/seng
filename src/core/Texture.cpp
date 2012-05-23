#include "stdafx.h"
#include "Texture.h"
#include "Graphics.h"

void Texture::load(
    unsigned char * data, 
    unsigned int width, 
    unsigned int height, 
    unsigned int paddedWidth, 
    unsigned int paddedHeight)
{
	this->width = width;
	this->height = height;
	this->paddedWidth = paddedWidth;
	this->paddedHeight = paddedHeight;
	maxU = width / static_cast<float>(paddedWidth);
	maxV = height / static_cast<float>(paddedHeight);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	Graphics::checkOpenglError("Texture::load Failed.");

	glGenTextures(1 , &openglTexture);
	Graphics::checkOpenglError("Texture::load Failed.");
   		
	// select our current texture
	glBindTexture(GL_TEXTURE_2D, openglTexture);
	Graphics::checkOpenglError("Texture::load Failed.");

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Graphics::checkOpenglError("Texture::load Failed.");

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Graphics::checkOpenglError("Texture::load Failed.");

	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	Graphics::checkOpenglError("Texture::load Failed.");

	//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	//graphicsGl->openGlCheckError("TextureGl::load Failed.");

	//get this done
	//glGenerateMipmap(GL_TEXTURE_2D);    // generate a mip map

}

void Texture::activate()
{
	glBindTexture(GL_TEXTURE_2D, openglTexture);
	Graphics::checkOpenglError("Texture::activate Failed.");
}

void Texture::deactivate()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	Graphics::checkOpenglError("Texture::deactivate Failed.");
}
