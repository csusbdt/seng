#pragma once

// This header will be pre-compiled.
// Make sure the include for this file is the first include in all files that use it
// and don't have anything before it.

// Windows-specific headers
#include "targetver.h"
#include <windows.h>
#include <dsound.h>

// General headers
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

#include "lua.hpp"

#include "snappy.h"

// strsafe.h must follow tchar.h 
#include <strsafe.h>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

