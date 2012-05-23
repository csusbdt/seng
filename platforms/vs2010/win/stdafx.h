#pragma once

// This header will be pre-compiled.
// Make sure the include for this file is the first include in all files that use it
// and don't have anything before it.

// Windows-specific headers
#include "targetver.h"
#include <windows.h>

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
#include <gl/gl.h>
#include <gl/glu.h>
#include "glext.h"
#include "wglext.h"
#include "lua.hpp"

// strsafe.h must follow tchar.h 
#include <strsafe.h>
