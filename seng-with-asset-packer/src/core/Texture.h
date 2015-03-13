#ifndef SENG_TEXTURE_H
#define SENG_TEXTURE_H

#include "stdafx.h"

class Texture
{
public:
    Texture() : width(0), height(0), paddedWidth(0), paddedHeight(0), maxU(0), maxV(0), openGlTexture(0), mipmap(false), tile(false) { }
    ~Texture() { }
    unsigned int getWidth() { return width; }  
    unsigned int getHeight() { return height; } 
    unsigned int getPaddedWidth() { return paddedWidth; } 
    unsigned int getPaddedHeight() { return paddedHeight; }
    float getMaxU() { return maxU; }
    float getMaxV() { return maxV; }
    bool activate();
    bool deactivate();
    bool load(unsigned char * data, unsigned int width, unsigned int height, unsigned int paddedWidth, unsigned int paddedHeight, bool generateMipmap = false);
    void setTiling(bool tile) { this->tile = tile; }

private:
	unsigned int width;
	unsigned int height;
	unsigned int paddedWidth;
	unsigned int paddedHeight;
	float maxU;
	float maxV;
    bool mipmap;
    bool tile;

    GLenum openGlTexture;

	Texture(const Texture &) { assert(false); }
	void operator=(const Texture &) { assert(false); }

};

#endif
