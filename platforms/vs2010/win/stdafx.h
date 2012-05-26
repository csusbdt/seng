#pragma once

// This header will be pre-compiled.
// Make sure the include for this file is the first include in all files that use it
// and don't have anything before it.

// Windows-specific headers
#include "targetver.h"
#include <windows.h>

// General headers
//#include <cstring>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <cassert>

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "GLES2/gl2platform.h"

//#include <gl/gl.h>
//#include <gl/glu.h>
#include "lua.hpp"

//#include "glext.h"
//#include "wglext.h"
//#include "glxext.h"  Linux-specific

// strsafe.h must follow tchar.h 
#include <strsafe.h>

/*
#define SENJ_GET_PROC_ADDRESS wglGetProcAddress

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGETATTRIBLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;

extern PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix4fvARB;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLUNIFORM1IARBPROC glUniform1iARB;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1IPROC glUniform1i;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib") 
*/
