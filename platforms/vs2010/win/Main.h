#include "stdafx.h"
#include "Core.h"

/**
 * \class Main
 *
 * \brief Windows-specific code (internal).
 */
class Main
{
public:    
    /**
     * \brief Program entry point.
     */
    static int main(int argc, _TCHAR* argv[]);

    static bool waitForConsoleToClose;

private:
    /**
     * The application's graphical window handle.
     */
    static HWND applicationWindowHandle;

    /**
     * The application's console window handle.
     */
    static HWND consoleWindowHandle;
    
    /**
     * The time that the process started.
     */
    static LARGE_INTEGER startTime;

    /**
     * The frequency of the high-resolution performance counter in counts per second.
     */
    static double timeCounterFrequency;

    /**
     * Device context handle
     */
    static HDC deviceContext;

    /**
     * Not sure why we need this.
     */
    static HGLRC renderContext;


    static EGLint frameBufferAttributes[];
    static EGLConfig frameBufferConfiguration;
    static EGLint numFrameBufferConfigurations;

    static EGLDisplay eglDisplay;
    static EGLSurface eglSurface;
    static EGLContext eglContext;

    /**
     * \brief Thread start for console input loop.
     *
     * The thread that runs this function reads lines 
     * from the console and passes them to Core through
     * the pointer Core::luaChunk.
     *
     * Only used when _DEBUG is defined.
     */
    static DWORD WINAPI consoleThread(LPVOID lpParam);

    /**
     * The Windows procedure.  
     * This is called to process window messages such as 
     * mouse move, key press, window closing, etc).
     */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /**
     * \brief Display the last Windows error in a dialog box and then terminate.
     *
     * \todo Call ErrorExit in Windows code.
     *
     * Taken from MSDN.
     */
    static void ErrorExit(LPTSTR lpszFunction);

    static void checkEglError(const std::string & msg);
    static void createContext();
    static void destroyContext();

    friend class Platform;
};

