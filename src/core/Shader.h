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
//#ifdef _WIN32
	void readShaderObject(std::string name, GLuint shaderObject);
//#else
//	void readShaderObject(std::string name, GLhandleARB shaderObject);
//#endif
    
private:
    GLuint programObject;
//#ifdef _WIN32
	GLuint vertexShaderObject;
	GLuint fragmentShaderObject;
//#else
//	GLhandleARB vertexShaderObject;
//	GLhandleARB fragmentShaderObject;
//#endif
    
	Shader(const Shader &) { assert(false); }
	void operator=(const Shader &) { assert(false); }
};

#endif
