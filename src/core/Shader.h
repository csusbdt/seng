#ifndef PROJ_SHADER_H
#define PROJ_SHADER_H

#include "stdafx.h"

class Matrix;
class Texture;

class Shader
{
public:
	Shader() { }
    ~Shader() { }
	void activate(bool picking);
	void deactivate();
	void setMatrix(const std::string & name, Matrix * m);
	//void setTexture(const std::string & name, Texture * texture);
	void setPickColor(float pickColor[4]);
    void load(const std::string & shaderSourceCode);
	void readShaderObject(std::string name, GLuint shaderObject);

private:
    GLuint programObject;
	GLuint vertexShaderObject;
	GLuint fragmentShaderObject;

	Shader(const Shader &) { assert(false); }
	void operator=(const Shader &) { assert(false); }
};

#endif
