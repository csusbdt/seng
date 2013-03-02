#include "stdafx.h"
#include "Core.h"
#include "Script.h"
#include "Graphics.h"
#include "Platform.h"

const double Core::minDt = 0.01; 
const double Core::maxDt = 0.1;

bool Core::run = true;
lua_State * Core::lua = NULL;
char * Core::luaChunk = NULL;

void Core::init()
{
    lua = luaL_newstate();
    assert(lua != 0);
    luaL_checkversion(lua);

    // Stop garbage collector.
    lua_gc(lua, LUA_GCSTOP, 0); 

    // Load Lua core libraries.
    // \todo maybe don't load lua libraries to save memory (and omit from build).
    luaL_openlibs(lua);

    // Register core function with Lua.
    lua_register(lua, "create", Script::create);
    lua_register(lua, "destroy", Script::destroy);
    lua_register(lua, "help", Script::help);
    lua_register(lua, "moveby", Script::moveby);
    lua_register(lua, "moveto", Script::moveto);
    lua_register(lua, "quit", Script::quit);
    lua_register(lua, "setBackgroundColor", Script::setBackgroundColor);

    // Restart garbage collector.
    lua_gc(lua, LUA_GCRESTART, 0);

    doFile("scripts/init.lua");

    Graphics::init();
}

void Core::onMessageQueueEmpty(double elapsedSeconds)
{
    if (!run)
    {
        return;
    }

    if (luaChunk != NULL)
    {
        doString(luaChunk);
        luaChunk = NULL;
    }

    static double previousElapsedSeconds = 0;
    static double dt = 0;

    dt += elapsedSeconds - previousElapsedSeconds;
    previousElapsedSeconds = elapsedSeconds;

    if (dt < minDt)
    {
        return;
    }

    if (dt > maxDt)
    {
        dt = maxDt;
    }

    // \todo Update all entities with dt.

    // dt is an accumulator; it has just been
    // consumed, so now it should be cleared.
    dt = 0;
}

void Core::renderNextFrame()
{
    if (run)
    {
        Graphics::renderNextFrame();
    }
}

void Core::onWindowClosing()
{
    run = false;
}

void Core::shutdown()
{
    if (lua != NULL)
    {
        lua_close(lua);
        lua = NULL;
    }
    Graphics::shutdown();
}

void Core::doFile(const char * filename) 
{
    int result = luaL_loadfile(lua, filename);
    if (result != LUA_OK)
    {
        fprintf(stderr, "Lua error message: %s\n\n", lua_tostring(lua, -1));
    }
    result = lua_pcall(lua, 0, 0, 0);
    if (result != LUA_OK) 
    {
        fprintf(stderr, "Lua error message: %s\n\n", lua_tostring(lua, -1));
    }
}

void Core::doString(const char * chunk) 
{
    int result = luaL_loadbuffer(lua, chunk, strlen(chunk), "");
    if (result != LUA_OK)
    {
        fprintf(stderr, "Error: %s\n\n", lua_tostring(lua, -1));
    }
    result = lua_pcall(lua, 0, 0, 0);
    if (result != LUA_OK) 
    {
        fprintf(stderr, "Error: %s\n\n", lua_tostring(lua, -1));
    }
}
