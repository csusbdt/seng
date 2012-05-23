#ifndef PROJ_CORE_H
#define PROJ_CORE_H

#include "stdafx.h"


/**
 * \class Core
 * 
 * \brief Main interface with platform-specific code.
 */
class Core
{
public:
    /**
     *
     */
//    typedef void (VoidFunction)();

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
     */
    static void init();
//    static void init(VoidFunction * swapBuffers);

    /**
     * Called by platform code when no window messages are pending.
     *
     * \param elapsedSeconds seconds elapsed from program start.
     */
    static void onMessageQueueEmpty(double elapsedSeconds);

    /**
     * Called by platform code when user closes application window.
     */
    static void onWindowClosing();

    /**
     * Shutdown program.
     */
    static void shutdown();

private:
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
     * \brief Run a Lua chunk stored in a file.
     *
     * Do not accept any returned values.
     */
    static void doFile(const char * filename);

    /**
     * \brief Run a Lua chunk stored in a string.
     *
     * Do not accept any returned values.
     */
    static void doString(const char * chunk);

};

#endif
