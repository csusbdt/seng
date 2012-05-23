#ifndef PROJ_SCRIPT_H
#define PROJ_SCRIPT_H

#include "stdafx.h"

/**
 * \class Script
 * 
 * \brief Container of functions that can be called from Lua script.
 */
class Script
{
public:
    /**
     * Quit application.
     */
    static int quit(lua_State * lua);
    
    /**
     * Set the background color.
     */
    static int setBackgroundColor(lua_State * lua);
    
    /**
     * Load sound file.
     */
    static int loadSound(lua_State * lua);
    
private:

};

#endif
