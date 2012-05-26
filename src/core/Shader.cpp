#include "stdafx.h"
#include "Shader.h"
#include "Graphics.h"
#include "Platform.h"
#include "Matrix.h"
//#include "Texture.h"

#define BUFFER_OFFSET(i) ((char *)0 +(i))

/**
 * Load the vertex and fragment shaders from the file system.
 *
 * \param shaderName The filename of two files ending in .vert and .frag.
 */
void Shader::load(const std::string & shaderName)
{
//	GLint linked;
//
//    std::string vertexShaderFilename = shaderName + ".vert"; 
//	std::string pixelShaderFilename = shaderName + ".frag";	
//
////	vertexShaderObject = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
//	vertexShaderObject = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
//	fragmentShaderObject = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
//
//	readShaderObject(vertexShaderFilename, vertexShaderObject);
//	Graphics::checkOpenglError("Shader::load glAttachShader Failed for readShaderObject.");
//
//	readShaderObject(pixelShaderFilename, fragmentShaderObject);
//	Graphics::checkOpenglError("Shader::load glAttachShader Failed for readShaderObject.");
//   	
//	// Create a program object and attach the two compiled shaders.
//
//	programObject = glCreateProgram();
//    glAttachShader(programObject, vertexShaderObject);
//	Graphics::checkOpenglError("Shader::load glAttachShader Failed for vertexShaderObject.");
//
//    glAttachShader(programObject, fragmentShaderObject);
//	Graphics::checkOpenglError("Shader::load glAttachShader Failed for fragmentShaderObject.");
//
//    // Link the program object.
//
//	glLinkProgram(programObject);
//	Graphics::checkOpenglError("Shader::load glLinkProgram Failed.");
//
//	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
//	if (linked == GL_FALSE)
//	{
//		int infologLength = 0;
//		int maxLength;
//		char *infoLog;
//	
//		glGetShaderiv(programObject, GL_INFO_LOG_LENGTH, &maxLength);
//		infoLog = (char *) malloc(maxLength);
//
//		glGetShaderInfoLog(programObject, maxLength, &infologLength, infoLog);
//
//		if (infologLength > 0)
//        {
//			printf("%s\n", infoLog);
//        }
//        Platform::fatalError("Shader::load glLinkProgram Error Linking.");
//	}
    
	/*GLint loc1 = glGetAttribLocation(programObject, "texture_coordinateIn");
	if ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		graphicsGl->openglFatalError(errorCode,"ShaderGl::load glGetAttribLocation Failed.");	    
	}
	if (loc1 == -1)
	{
		util->fatalError("ShaderGl::load glGetUniformLocation returned -1");
	}
	
	GLint loc2 = glGetAttribLocation(programObject, "texture_coordinateIn");
	if ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		graphicsGl->openglFatalError(errorCode,"ShaderGl::load glGetAttribLocation Failed.");	    
	}
	if (loc2 == -1)
	{
		util->fatalError("ShaderGl::load glGetUniformLocation returned -1");
	}*/
}

void Shader::setMatrix(const std::string & name, Matrix * matrix)
{
	Matrix * mat = static_cast<Matrix *>(matrix);
	float a[4][4];
	for(int i= 0; i<4;i++)
	{
		for(int j= 0; j<4;j++)
		{
			a[i][j] = mat->matrix[i+j];
		}
	}

	//glUseProgram(programObject);
	//
	//GLint loc = glGetUniformLocationARB(programObject, name.c_str());
	////GLint loc = glGetUniformLocation(programObject, "my_color_texture");
 //   Graphics::checkOpenglError("Shader::setMatrix glGetUniformLocation Failed.");	    

	//if (loc == -1)
	//{
	//	Platform::fatalError("Shader::setMatrix glGetUniformLocation returned -1");
	//}	

	//glUniformMatrix4fvARB(loc, 1, false, mat->matrix);
	////glUniformMatrix4fvARB(loc, 1, false,&a[0][0]);
 //   Graphics::checkOpenglError("Shader::setMatrix glGetUniformLocation Failed.");	    
}

void Shader::activate(bool picking)
{	
 //   glUseProgram(programObject);
	//if(picking == true)
	//{
	//	//set value for pick in shader to 1
	//	GLint loc = glGetUniformLocationARB(programObject, "pick");
 //       Graphics::checkOpenglError("Shader::activate glGetUniformLocation Failed.");	    

	//	if (loc == -1)
	//	{
	//		Platform::fatalError("Shader::activate glGetUniformLocation returned -1");
	//	}
	//
	//	glUniform1i(loc, 1);
 //       Graphics::checkOpenglError("Shader::setPickColor glGetUniformLocation Failed.");	    
	//}
	//else
	//{
	//	//set value for pick in shader to 0
	//	GLint loc = glGetUniformLocationARB(programObject, "pick");
	//	if ((errorCode = glGetError()) != GL_NO_ERROR)
	//	{
	//		graphicsGl->openglFatalError(errorCode,"ShaderGl::activate glGetUniformLocation Failed.");	    
	//	}

	//	if (loc == -1)
	//	{
	//		util->fatalError("ShaderGl::activate glGetUniformLocation returned -1");
	//	}
	//
	//	glUniform1i(loc, 0);
	//
	//	if ((errorCode = glGetError()) != GL_NO_ERROR)
	//	{
	//		graphicsGl->openglFatalError(errorCode,"ShaderGl::setPickColor glGetUniformLocation Failed.");	    
	//	}
	//}
}

void Shader::deactivate()
{
	//glUseProgram(programObject);
	////set value for pick in shader to 0
	//GLint loc = glGetUniformLocationARB(programObject, "pick");
 //   Graphics::checkOpenglError("Shader::activate glGetUniformLocation Failed.");	    

	//if (loc == -1)
	//{
	//	Platform::fatalError("Shader::activate glGetUniformLocation returned -1");
	//}
	//
	//glUniform1i(loc, 0);
	//
 //   Graphics::checkOpenglError("Shader::setPickColor glGetUniformLocation Failed.");	    
}
/*
void Shader::setTexture(const std::string & name, Texture * texture)
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
    Graphics::checkOpenglError("ShaderGl::setMatrix glGetUniformLocation Failed.");	    

	glBindTexture(GL_TEXTURE_2D, texture->openglTexture);
    Graphics::checkOpenglError("ShaderGl::setMatrix glGetUniformLocation Failed.");	    

	glEnable(GL_TEXTURE_2D);
    Graphics::checkOpenglError("ShaderGl::setMatrix glGetUniformLocation Failed.");	    
	
	glUseProgram(programObject);

	GLint loc = glGetUniformLocationARB(programObject, name.c_str());
    Graphics::checkOpenglError("ShaderGl::load glGetUniformLocation Failed.");	    
	if (loc == -1)
	{
        Platform::fatalError("ShaderGl::load glGetUniformLocation returned -1");
	}

	glUniform1iARB(loc, 0 );
    Graphics::checkOpenglError("ShaderGl::load glGetUniformLocation Failed.");	    
}

void Shader::setPickColor(float pickColor[4])
{
	glUseProgram(programObject);
	
	GLint loc = glGetUniformLocationARB(programObject, "pickColor");
    Graphics::checkOpenglError("ShaderGl::setPickColor glGetUniformLocation Failed.");	    

	if (loc == -1)
	{
        Platform::fatalError("ShaderGl::setPickColor glGetUniformLocation returned -1");
	}
	
	glUniform4f(loc, pickColor[0], pickColor[1], pickColor[2], 1.0f);
    Graphics::checkOpenglError("ShaderGl::setPickColor glGetUniformLocation Failed.");	    
}
*/
#ifdef _WIN32
void Shader::readShaderObject(std::string name, GLuint shaderObject)
#else
void Shader::readShaderObject(std::string name, GLhandleARB shaderObject)
#endif
{
    // Allocate memory to hold the source of our shaders.
    FILE * fp;
    int count;
    int pos;
    int shaderSize;
    GLchar * shader = NULL; 
	GLint compiled;  // status values
	
    fp = fopen(name.c_str(), "r");
    if (!fp)
	{
        Platform::fatalError("Shader::readShaderObject Error Opening File."); 
	}
    
	pos = (int) ftell (fp);
    fseek(fp, 0, SEEK_END);		        // move to end
    shaderSize = (int) ftell(fp) - pos;	// calculates file size	
    fseek(fp, 0, SEEK_SET); 			// rewind to beginning
     
    if (shaderSize <= 0)
	{
		Platform::fatalError("Shader::readShaderObject File Empty.");     
    }

    shader = (GLchar *) malloc(shaderSize + 1);
    
    // Read the source code
    count = (int) fread(shader, 1, shaderSize, fp);
    (shader)[count] = '\0';

    if (ferror(fp))
    {
        count = 0;
    }

    fclose(fp);
	
	// Load source code strings into shaders, compile and link
	//glShaderSource(shaderObject, 1 ,const_cast<const GLchar**>(&shader), NULL);
 //   Graphics::checkOpenglError("Shader::readShaderObject glShaderSource Failed.");
	//	
 //   glCompileShader(shaderObject);
	//Graphics::checkOpenglError("Shader::readShaderObject glCompileShader Failed.");

	//glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);
	//if(compiled == GL_FALSE)
	//{
	//	int infologLength = 0;
	//	int maxLength;
	//	char *infoLog;
	//
	//	glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &maxLength);
	//	infoLog = (char *) malloc(maxLength);

	//	glGetShaderInfoLog(shaderObject, maxLength, &infologLength, infoLog);

	//	if (infologLength > 0)
 //       {
	//		printf("%s\n", infoLog);
 //       }

	//	Platform::fatalError("ShaderGl::readShaderObject Compile Failed.");
	//}	
	//free(shader);     
}
