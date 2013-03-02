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
     * Create a thing.
     */
    static int create(lua_State * lua);
        
    /**
     * Destroy a thing.
     */
    static int destroy(lua_State * lua);

    /**
     * Display list of seng functions.
     */
    static int help(lua_State * lua);    
        
    /**
     * Move a thing by an offset.
     */
    static int moveby(lua_State * lua);
        
    /**
     * Move a thing to a world position.
     */
    static int moveto(lua_State * lua);

    /**
     * Quit application.
     */
    static int quit(lua_State * lua);
    
    /**
     * Set the background color.
     */
    static int setBackgroundColor(lua_State * lua);
        
private:

};

#endif
