#include "stdafx.h"
#include "Script.h"
#include "Core.h"
#include "Graphics.h"
#include "Thing.h"
#include "PlayerController.h"

// Helper functions.

float clamp(lua_Number x, lua_Number a, lua_Number b)
{
    return x < a ? (float)a : (x > b ? (float)b : (float)x);
}

unsigned int Script::checkArgs(lua_State * L, unsigned int minArgs, unsigned int maxArgs)
{
    int arguments = lua_gettop(L);
    assert(arguments >= 0);
    unsigned int args = static_cast<unsigned int>(arguments);
    if (args < minArgs || args > maxArgs)
    {
        luaL_error(L, "Requires %d to %d arguments.", minArgs, maxArgs);
        assert(false);  // luaL_error never returns.
    }
    return args;
}

Thing * Script::findThing(lua_State * L, unsigned int argPos)
{
    const char * name = luaL_checkstring(L, argPos);
    if (name == NULL)
    {
        luaL_error(L, "Name can not be nil.");
    }
    Thing * thing = Thing::find(name);
    if (thing == NULL)
    {
        luaL_error(L, "There is nothing with the name %s.", name);
    }
    return thing;
}

// Global functions.

int Script::quit(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 0)
    {
        return luaL_error(L, "quit takes no arguments");
    }
    Core::run = false;
    return 0;
}

int Script::backgroundColor(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 3)
    {
        return luaL_error(L, "setBackgroundColor requires 3 arguments: red, green, blue");
    }
    lua_Number red = luaL_checknumber(L, 1);
    lua_Number green = luaL_checknumber(L, 2);
    lua_Number blue = luaL_checknumber(L, 3);

    Graphics::backgroundColorRed = clamp(red, 0, 1);
    Graphics::backgroundColorGreen = clamp(green, 0, 1);
    Graphics::backgroundColorBlue = clamp(blue, 0, 1);

    return 0;
}

//int Script::scene(lua_State * L)
//{
//    int numberOfArguments = lua_gettop(L);
//    if (numberOfArguments != 1)
//    {
//        return luaL_error(L, "scene requires 1 argument: [scene file pathname]");
//    }
//    const char * fileName = luaL_checkstring(L, 1);
//    if (fileName != NULL)
//    {
//        Scene::load(fileName);
//    }
//    return 0;
//}

int Script::create(lua_State * L)
{
    checkArgs(L, 1, 1);
    const char * name = luaL_checkstring(L, 1);
    assert(name != NULL);
    Thing::create(name);
    return 0;
}

// Thing operations.

int Script::destroy(lua_State * L)
{
    checkArgs(L, 1, 1);
    Thing * thing = findThing(L);
    Thing::destroy(thing->getName());
    return 0;
}

int Script::pc(lua_State * L)
{
    checkArgs(L, 1, 1);
    Thing * thing = findThing(L);
    PlayerController::setPlayerThing(thing);
    return 0;
}

/**
 * Set/get the position of a thing.
 * 
 * This function always returns the x,y,z coordinates of the designated thing.
 * You can set the x,y,z coordinates depending on how many arguments are used.
 *
 * Examples:
 *    x,y,z = pos("a") -- gets the position of "a".
 *    x,y,z = pos("a", 1) -- sets the x coord of a
 *    x,y,z = pos("a", 1, 1) -- sets the x and y coordinates of "a"
 *    x,y,z = pos("a", 1, 1, 2) -- sets the x, y and z coordinates of "a"
 */
int Script::pos(lua_State * L)
{
    int args = checkArgs(L, 1, 4);
    Thing * thing = findThing(L);
    if (args > 1)
    {
        thing->x = luaL_checknumber(L, 2);
    }
    if (args > 2)
    {
        thing->y = luaL_checknumber(L, 3);
    }
    if (args > 3)
    {
        thing->z = luaL_checknumber(L, 4);
    }
    lua_pushnumber(L, thing->x);
    lua_pushnumber(L, thing->y);
    lua_pushnumber(L, thing->z);
    return 3;
}

/**
 * Offset the position of a thing.
 * 
 * This function always returns the x,y,z coordinates of the designated thing.
 * You can offset the x,y,z coordinates depending on how many arguments are used.
 *
 * Examples:
 *    x,y,z = move("a") -- gets the position of "a".
 *    x,y,z = move("a", 1) -- offsets the x coord of a
 *    x,y,z = move("a", 1, 1) -- offsets the x and y coordinates of "a"
 *    x,y,z = move("a", 1, 1, 2) -- offsets the x, y and z coordinates of "a"
 */
int Script::move(lua_State * L)
{
    int args = checkArgs(L, 1, 4);
    Thing * thing = findThing(L);
    if (args > 1)
    {
        thing->x += luaL_checknumber(L, 2);
    }
    if (args > 2)
    {
        thing->y += luaL_checknumber(L, 3);
    }
    if (args > 3)
    {
        thing->z += luaL_checknumber(L, 4);
    }
    lua_pushnumber(L, thing->x);
    lua_pushnumber(L, thing->y);
    lua_pushnumber(L, thing->z);
    return 3;
}

int Script::tone(lua_State * L)
{
    unsigned int args = checkArgs(L, 1, 3);
    Thing * thing = findThing(L);
    if (args > 1)
    {
        thing->frequency += luaL_checknumber(L, 2);
    }
    if (args > 2)
    {
        thing->amplitude += luaL_checknumber(L, 3);
    }
    lua_pushnumber(L, thing->frequency);
    lua_pushnumber(L, thing->amplitude);
    return 2;
}
