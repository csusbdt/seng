#ifndef PROJ_CORE_H
#define PROJ_CORE_H

#include "stdafx.h"
#include "AssetContainer.h"

/**
 * \class Core
 * 
 * \brief Main interface with platform-specific code.
 */
class Core
{
public:
    /**
     * Subsystems will shut down when this is set to false.
     */
    static bool run;

    /**
     * Maximum line length of Lua commands entered into console window.
     * \sa luaChunk
     */
    static const unsigned int maxLuaLineSize = 100;
    
    /** 
     * \brief Pointer used to pass messages between main thread and console input thread.
     *
     * If luaChunk is not null, then the main thread should 
     * execute the chunk and set luaChunk to null; the thread
     * reading commands will wait until luaChunk is null.
     *
     * \sa maxLuaLineSize
     */
    static char * luaChunk;

    /**
     * Called by platform code.
     * Spawns thread that reads console input and passes to main thread.
     * \param swapBuffers pointer to function in platform code that swaps the graphics buffers
     * \return false on error
     */
    static bool init();

    /**
     * Called by platform code when no window messages are pending.
     *
     * \param elapsedSeconds seconds elapsed from program start.
     */
    static void onMessageQueueEmpty(double elapsedSeconds);

    static void renderNextFrame();

    /**
     * Called by platform code when user closes application window.
     */
    static void onWindowClosing();

    /**
     * Called by platform code when user presses A key.
     */
    static void onKeyDownA();
    static void onKeyDownD();
    static void onKeyDownS();
    static void onKeyDownW();
    static void onKeyDownEsc();

    /**
     * Called by platform code when user releases A key.
     */
    static void onKeyUpA();
    static void onKeyUpD();
    static void onKeyUpS();
    static void onKeyUpW();
    static void onKeyUpEsc();

    /**
     * Shutdown program.
     */
    static void shutdown();

    /**
     * \brief Run a Lua chunk stored in a file.
     *
     * Do not accept any returned values.
     */
//    static void doFile(const char * filename);

    /**
     * \brief Run a Lua chunk stored in a string.
     *
     * Do not accept any returned values.
     */
    static void doString(const char * chunk);

private:
	DISALLOW_COPY_AND_ASSIGN(Core);

    /**
     * Provides access to project assets.
     */
    static asset::AssetContainer assetContainer;

    /**
     * Swap buffer function set by platform code.
     */
//    static VoidFunction * swapBuffers;

    /**
     * The minimum dt used to update game logic.
     */
    static const double minDt; 

    /**
     * The maximum dt used to update game logic.
     */
    static const double maxDt;

    /**
     * The Lua virtual machine.
     */
    static lua_State * lua;

    /**
     * The currently loaded scene.
     */
    //static Scene * scene;

};

#endif
