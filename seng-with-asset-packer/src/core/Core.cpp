#include "stdafx.h"
#include "Core.h"
#include "Script.h"
#include "Graphics.h"
#include "Platform.h"
#include "Util.h"
#include "PlayerController.h"

const double Core::minDt = 0.01;
const double Core::maxDt = 0.1;

bool Core::run = true;
lua_State * Core::lua = NULL;
char * Core::luaChunk = NULL;
asset::AssetContainer Core::assetContainer;

bool Core::init()
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
    lua_register(lua, "quit", Script::quit);
    lua_register(lua, "backgroundColor", Script::backgroundColor);
    lua_register(lua, "create", Script::create);
    lua_register(lua, "pos", Script::pos);
    lua_register(lua, "move", Script::move);
    lua_register(lua, "destroy", Script::destroy);
    lua_register(lua, "pc", Script::pc);
    lua_register(lua, "tone", Script::tone);

    // Restart garbage collector.
    lua_gc(lua, LUA_GCRESTART, 0);

    if (!Graphics::init())
    {
        return false;
    }

    if (!assetContainer.setContainerFilename("content.seng"))
    {
		Platform::error << "Failed to load content file: content.seng" << std::endl << std::endl;
		Platform::error << "AssetContainer error: " << assetContainer.getLastError() << std::endl << std::endl;
        return false;
    }
    char initScript[1024];
    if (!assetContainer.getString("scripts/init.lua", initScript, 1024))
    {
		Platform::error << "AssetContainer error: " << assetContainer.getLastError();
        return false;
    }
    doString(initScript);
    return true;
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
    PlayerController::tick(dt);

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

void Core::onKeyDownA()
{
    PlayerController::moveLeft = true;
    printf("A down\n");
}

void Core::onKeyDownD()
{
    PlayerController::moveRight = true;
    printf("D down\n");
}

void Core::onKeyDownS()
{
    PlayerController::moveDown = true;
    printf("S down\n");
}

void Core::onKeyDownW()
{
    PlayerController::moveUp = true;
    printf("W down\n");
}

void Core::onKeyDownEsc()
{
    printf("Esc down\n");
}

void Core::onKeyUpA()
{
    PlayerController::moveLeft = false;
    printf("A up\n");
}

void Core::onKeyUpD()
{
    PlayerController::moveRight = false;
    printf("D up\n");
}

void Core::onKeyUpS()
{
    PlayerController::moveDown = false;
    printf("S up\n");
}

void Core::onKeyUpW()
{
    PlayerController::moveUp = false;
    printf("W up\n");
}

void Core::onKeyUpEsc()
{
    printf("Esc up\n");
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
