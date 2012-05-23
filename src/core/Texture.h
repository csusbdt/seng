#ifndef GENG_TEXTURE_H
#define GENG_TEXTURE_H

#include "stdafx.h"

class Texture
{
public:
    unsigned int getWidth() { return width; }  
    unsigned int getHeight() { return height; } 
    unsigned int getPaddedWidth() { return paddedWidth; } 
    unsigned int getPaddedHeight() { return paddedHeight; }
    float getMaxU() { return maxU; }
    float getMaxV() { return maxV; }
    void activate();
    void deactivate();
    void load(unsigned char * data, unsigned int width, unsigned int height, unsigned int paddedWidth, unsigned int paddedHeight);

protected:
    unsigned int width;
    unsigned int height;
    unsigned int paddedWidth;
    unsigned int paddedHeight;
    float maxU;
    float maxV;

private:
    unsigned int openglTexture;

    Texture() : width(0), height(0), paddedWidth(0), paddedHeight(0), maxU(0), maxV(0) { }
    Texture(const Texture &) { assert(false); }
	virtual ~Texture() { }
	void operator=(const Texture &) { assert(false); }	
};

#endif
