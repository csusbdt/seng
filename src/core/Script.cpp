#include "stdafx.h"
#include "Script.h"
#include "Core.h"
#include "Graphics.h"
#include "Thing.h"

float clamp(lua_Number x, lua_Number a, lua_Number b)
{
    return x < a ? (float)a : (x > b ? (float)b : (float)x);
}

int Script::create(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 1)
    {
        return luaL_error(L, "create requires 1 argument: name");
    }
    const char * name = luaL_checkstring(L, 1);
    if (name != NULL)
    {
        Thing::create(name);
    }
    return 0;
}

int Script::destroy(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 1)
    {
        return luaL_error(L, "destroy requires 1 argument: name");
    }
    const char * name = luaL_checkstring(L, 1);
    if (name == NULL)
    {
        return luaL_error(L, "name can not be nil");
    }
    Thing * thing = Thing::find(name);
    if (thing == NULL)
    {
        return luaL_error(L, "There is nothing with that name.");
    }
    Thing::destroy(name);
    return 0;
}

int Script::help(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 0)
    {
        return luaL_error(L, "help takes no arguments");
    }
    fprintf(stdout, "%s\n", "create(name)");
    fprintf(stdout, "%s\n", "destroy(name)");
    fprintf(stdout, "%s\n", "help()");
    fprintf(stdout, "%s\n", "moveby(name, dx, dy, dz)");
    fprintf(stdout, "%s\n", "moveto(name, x, y, z)");
    fprintf(stdout, "%s\n", "quit()");
    fprintf(stdout, "%s\n", "setBackgroundColor(r, g, b, a)");
    return 0;
}

int Script::moveby(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 4)
    {
        return luaL_error(L, "move requires 4 arguments: name, dx, dy, dz");
    }
    const char * name = luaL_checkstring(L, 1);
    if (name == NULL)
    {
        return luaL_error(L, "name can not be nil");
    }
    Thing * thing = Thing::find(name);
    if (thing == NULL)
    {
        return luaL_error(L, "There is nothing with that name.");
    }
    lua_Number dx = luaL_checknumber(L, 2);
    lua_Number dy = luaL_checknumber(L, 3);
    lua_Number dz = luaL_checknumber(L, 4);
    thing->x += dx;
    thing->y += dy;
    thing->z += dz;
    return 0;
}

int Script::moveto(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 4)
    {
        return luaL_error(L, "move requires 4 arguments: name, x, y, z");
    }
    const char * name = luaL_checkstring(L, 1);
    if (name == NULL)
    {
        return luaL_error(L, "name can not be nil");
    }
    Thing * thing = Thing::find(name);
    if (thing == NULL)
    {
        return luaL_error(L, "There is nothing with that name.");
    }
    lua_Number x = luaL_checknumber(L, 2);
    lua_Number y = luaL_checknumber(L, 3);
    lua_Number z = luaL_checknumber(L, 4);
    thing->x = x;
    thing->y = y;
    thing->z = z;
    return 0;
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
