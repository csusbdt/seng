#ifndef PROJ_SCRIPT_H
#define PROJ_SCRIPT_H

#include "stdafx.h"

class Thing;

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
    static int backgroundColor(lua_State * lua);
    
    /**
     * Set the background image.
     */
//    static int scene(lua_State * lua);
    
    /**
     * Create a thing.
     *
     * This function does nothing if named thing already exists.
     * Optionally, we can report an error.
     */
    static int create(lua_State * lua);
           
    /**
     * Designate a thing as the player character.
     */
    static int pc(lua_State * lua);
     
    /**
     * Get/set a thing's position.
     */
    static int pos(lua_State * lua);
        
    /**
     * Move a thing.
     * 
     * Returns the thing's new x,y,z position.
     */
    static int move(lua_State * lua);
        
    /**
     * Destroy a thing.
     */
    static int destroy(lua_State * lua);
        
    /**
     * Set a thing to emit a tone.
     */
    static int tone(lua_State * lua);
        
private:        
    /**
     * Find and return a named thing.
     */
    static Thing * findThing(lua_State * L, unsigned int argPos = 1);

    /**
     * Check for required number of arguments.
     *
     * @return number of arguments.
     */
    static unsigned int checkArgs(lua_State * L, unsigned int minArgs, unsigned int maxArgs);
};

#endif
