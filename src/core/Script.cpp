#include "stdafx.h"
#include "Script.h"
#include "Core.h"
#include "Graphics.h"

float clamp(lua_Number x, lua_Number a, lua_Number b)
{
    return x < a ? (float)a : (x > b ? (float)b : (float)x);
}

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

int Script::setBackgroundColor(lua_State * L)
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

int Script::loadSound(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 1)
    {
        return luaL_error(L, "loadSound requires 1 argument: filename");
    }
    //lua_Number red = luaL_checknumber(L, 1);
    //lua_Number green = luaL_checknumber(L, 2);
    //lua_Number blue = luaL_checknumber(L, 3);

    //Graphics::backgroundColorRed = clamp(red, 0, 1);
    //Graphics::backgroundColorGreen = clamp(green, 0, 1);
    //Graphics::backgroundColorBlue = clamp(blue, 0, 1);

    return 0;
}
