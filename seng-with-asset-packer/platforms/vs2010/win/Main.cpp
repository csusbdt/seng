#include "stdafx.h"

#include "Main.h"
#include "Platform.h"
#include "Graphics.h"
#include "Core.h"

/**
 * \brief Entry point. 
 *
 * The project is a console application.
 *
 * The Release and Debug configurations include the following defines:
 *   - _WIN32
 *   - _UNICODE
 *   - _CONSOLE
 *   - _CRT_SECURE_NO_WARNINGS
 *
 * The Debug configuration additionally includes the following:
 *   - _DEBUG
 *   - LUA_USE_APICHECK
 *
 * \todo Determine the effects of declaring this _tmain instead of main.
 */
int _tmain(int argc, _TCHAR* argv[])
{
    if (!Main::main(argc, argv))
    {
        Core::run = false;
        std::cerr << Platform::error.str() << std::endl;
#ifdef _DEBUG
        std::cin.get();
#endif
        return 1;
    }
    else
    {
        return 0;
    }
}

//..............................................................................
//
// Main class definitions
//
//..............................................................................

HWND Main::consoleWindowHandle = 0;
HWND Main::applicationWindowHandle = 0;
LARGE_INTEGER Main::startTime;
double Main::timeCounterFrequency = 0;
HDC Main::deviceContext;
HGLRC Main::renderContext;
bool Main::waitForConsoleToClose = false;

EGLint Main::frameBufferAttributes[] = { 
    EGL_RED_SIZE, 4,
    EGL_GREEN_SIZE, 4,
    EGL_BLUE_SIZE, 4,
    EGL_ALPHA_SIZE, 0,
    EGL_DEPTH_SIZE, 8,
    EGL_NONE 
};

EGLConfig Main::frameBufferConfiguration;
EGLint Main::numFrameBufferConfigurations = 0;
EGLDisplay Main::eglDisplay = EGL_NO_DISPLAY;
EGLSurface Main::eglSurface = EGL_NO_SURFACE;
EGLContext Main::eglContext = EGL_NO_CONTEXT;


bool Main::main(int argc, _TCHAR* argv[])
{
    consoleWindowHandle = GetConsoleWindow();

    /// Initialize time keeping.
    LARGE_INTEGER frequency;
    assert(QueryPerformanceFrequency(&frequency) != 0);
    timeCounterFrequency = static_cast<double>(frequency.QuadPart);
    assert(timeCounterFrequency > 0);
    QueryPerformanceCounter(&startTime);

    /// Register a window class. 
    /// \todo Configure small and large application icons.

    const wchar_t * windowClassName = L"x";
    WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= 0; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor		= 0; //LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;  //MAKEINTRESOURCE(IDC_MAIN);
	wcex.lpszClassName	= windowClassName;
	wcex.hIconSm		= 0; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	ATOM windowClass = RegisterClassExW(&wcex);
    assert(windowClass != 0);

    /// Determine size of window border by creating a temporary window.

    applicationWindowHandle = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        windowClassName,
        L"X",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
        CW_USEDEFAULT, 
		Platform::screenWidth, 
        Platform::screenHeight,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL);
    assert(applicationWindowHandle != NULL);
    RECT clientRect;
	GetClientRect(applicationWindowHandle, &clientRect);
	int clientRectWidth = clientRect.right;
	int clientRectHeight = clientRect.bottom; 
	RECT windowRect;
	GetWindowRect(applicationWindowHandle, &windowRect);
	int windowRectWidth = windowRect.right - windowRect.left;
	int windowRectHeight = windowRect.bottom - windowRect.top;    
	int windowBorderWidth = windowRectWidth - clientRectWidth;
	int windowBorderHeight = windowRectHeight - clientRectHeight;
	assert(DestroyWindow(applicationWindowHandle));
    Core::run = true;  // Temporary window sets this to false when destroyed.

	/// Calculate the window width and height needed to achieve
    /// the application's desired width and height.
	int windowWidth = Platform::screenWidth + windowBorderWidth;
	int windowHeight = Platform::screenHeight + windowBorderHeight;

    /// Create final application window.
	applicationWindowHandle = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        windowClassName,
        L"Project X",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
        CW_USEDEFAULT, 
		windowWidth, 
        windowHeight,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL);
    assert(applicationWindowHandle != NULL);
    ShowWindow(applicationWindowHandle, SW_SHOW);
    UpdateWindow(applicationWindowHandle);

#if _DEBUG
    /// When debugging, start thread to read Lua commands from console.
    CreateThread(0, 0, consoleThread, 0, 0, 0);
#else
    /// When not debugging, hide console.
    ShowWindow(consoleWindowHandle, SW_HIDE);
#endif

    deviceContext = GetDC(applicationWindowHandle);
    Platform::eglNativeWindowType = (EGLNativeWindowType) applicationWindowHandle;

    // Get the display handle.
    eglDisplay = Platform::getEglDisplay();
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        Platform::error << "No EGL Display.";
        return false;
    }

    // Check OpenGL ES version.    
    EGLint major;
    EGLint minor;
    eglInitialize(eglDisplay, &major, &minor);
    if (!checkEglError())
    {
        Platform::error << "eglInitialize failed.";
        return false;
    }
    if (major == 1 && minor < 4)
    {
        Platform::error << "EGL version 1.4 or later required.";
        return false;
    }

    memset(&frameBufferConfiguration, 0, sizeof(EGLConfig));  // Not sure this is needed.
    eglChooseConfig(eglDisplay, frameBufferAttributes, &frameBufferConfiguration, 1, &numFrameBufferConfigurations);
    if (!checkEglError())
    {
        Platform::error << "Call to eglChooseConfig failed.";
        return false;
    }
    if (numFrameBufferConfigurations == 0)
    {
        Platform::error << "No EGL frame buffer configurations that match the specified requirements.";
        return false;
    }

    // Create a window surface.
    EGLint surfaceAttributes[] = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER, EGL_NONE, EGL_NONE };
    eglSurface = eglCreateWindowSurface(eglDisplay, frameBufferConfiguration, Platform::eglNativeWindowType, surfaceAttributes);
    if (!checkEglError())
    {
        Platform::error << "eglCreateWindowSurface failed.";
        return false;
    }
    if (eglSurface == EGL_NO_SURFACE)
    {
        Platform::error << "Call to eglCreateWindowSurface failed.";
        return false;
    }

    if (!createContext())
    {
        return false;
    }

    if (!initAudio())
    {
        return false;
    }

    if (!Core::init())
    {
        return false;
    }

    /// Enter message loop.
    while (Core::run)
    {
        MSG Msg;
	    while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
	    {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
	    }

        // Core has not yet drawn requested frame.
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        double totalElapsedSeconds = static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / timeCounterFrequency;
        Core::onMessageQueueEmpty(totalElapsedSeconds);

        Core::renderNextFrame();

        // Core has drawn a frame, so let's render it.
        if (EGL_FALSE == eglSwapBuffers(eglDisplay, eglSurface))
        {
            // eglSwapBuffers will fail after a power event.
            // In this case, we need to reinitialize.
            EGLint error = eglGetError();	
            if (error == EGL_CONTEXT_LOST)
            {
                // Power event; need to "... destroy all contexts and reinitialise OpenGL ES state 
                // and objects to continue rendering." 
                destroyContext();
                if(!createContext())
                {
                    return false;
                }
            }
        }
    }

    Core::shutdown();

    destroyContext();
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);

    while (waitForConsoleToClose)
    {
        // Wait until user presses enter in console window.
    }

	ReleaseDC(Main::applicationWindowHandle, Main::deviceContext);
	return true;
}

DWORD WINAPI Main::consoleThread(LPVOID lpParam)
{
    static char line[Core::maxLuaLineSize];
    while (Core::run)
    {
        if (Core::luaChunk == NULL)
        {
            if (fgets(line, Core::maxLuaLineSize, stdin) == NULL)
            {
                // Either end of file or error.
                std::cerr << "WARNING: fgets returned NULL on stdin." << std::endl;
                std::cerr << "Exiting console read thread." << std::endl;
                return 0;
            }
            Core::luaChunk = line;
        }
        else
        {
            // Nothing to do, so let other threads run.
            Sleep(0);
        }
    }

    if (waitForConsoleToClose)
    {
        std::cout << "Press enter to terminate." << std::endl;
        std::cin.get();
        waitForConsoleToClose = false;
    }

    return 0;
}

LRESULT CALLBACK Main::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
    {
        if (wParam == 'A')
        {
            Core::onKeyDownA();
        } 
        else if (wParam == 'D')
        {
            Core::onKeyDownD();
        }
        else if (wParam == 'S')
        {
            Core::onKeyDownS();
        }
        else if (wParam == 'W')
        {
            Core::onKeyDownW();
        } 
        else if (wParam == VK_ESCAPE)
        {
            Core::onKeyDownEsc();
        }
    }
    else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
    {
        if (wParam == 'A')
        {
            Core::onKeyUpA();
        }
        else if (wParam == 'D')
        {
            Core::onKeyUpD();
        }
        else if (wParam == 'S')
        {
            Core::onKeyUpS();
        }
        else if (wParam == 'W')
        {
            Core::onKeyUpW();
        }
        else if (wParam == VK_ESCAPE)
        {
            Core::onKeyUpEsc();
        }
    }
	else if (msg == WM_CLOSE)
    {
        Core::onWindowClosing();
        DestroyWindow(applicationWindowHandle);
	}
    else if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    else
    {
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
	return 0;
}

void Main::ErrorExit(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}

bool Main::checkEglError()
{
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
    {
        Platform::error << "EGL error: " << error << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * \brief Create a new context and make it current.
 *
 * This function is called at program start up and after power events.
 */
bool Main::createContext()
{
    assert(eglContext == EGL_NO_CONTEXT);
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, frameBufferConfiguration, EGL_NO_CONTEXT, contextAttributes);
    if (!checkEglError())
    {
        Platform::error << "eglCreateContext failed.";
        return false;
    }
    if (eglContext == EGL_NO_CONTEXT)
    {   
        Platform::error << "eglCreateContext returned EGL_NO_CONTEXT";
        return false;
    }
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    if (!checkEglError())
    {
        Platform::error << "eglMakeCurrent failed.";
        return false;
    }
    return true;
}

/**
 * \brief Initialize audio service.
 *
 *  Documentation: http://msdn.microsoft.com/en-us/library/windows/desktop/ee416960(v=vs.85).aspx
 */
bool Main::initAudio()
{
    LPDIRECTSOUND8 pds;
    HRESULT result = DirectSoundCreate8(NULL, &pds, NULL);
    if (result != DS_OK)
    {
        Platform::error << "DirectSoundCreate8() failed.";
        return false;
    }
    result = pds->SetCooperativeLevel(applicationWindowHandle, DSSCL_NORMAL);
    if (result != DS_OK)
    {
        return false;
    }
    return true;
}

/**
 * \brief Destroy the context.
 *
 * This function is called after power events and at shutdown.
 * I'm not sure that I am handling power events correctly.
 */
bool Main::destroyContext()
{
    assert(eglContext != EGL_NO_CONTEXT);

    // Make sure the context is not current.
    if (eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
    {
        EGLint error = eglGetError();
        if (error == EGL_CONTEXT_LOST)
        {
            std::cout << "WARNING: Power event when trying to initialize.  I don't know how to handle this." << std::endl;
            eglContext = EGL_NO_CONTEXT;
            return true;
        }
        else
        {
            std::cout << "WARNING: eglMakeCurrent failed in Graphics::initializeOpenglState.  Maybe this is normal when power events occur." << std::endl;
            eglContext = EGL_NO_CONTEXT;
            return true;
        }
    }

    // Destroy the context.
    eglDestroyContext(eglDisplay, eglContext);
    if (!checkEglError())
    {
        std::cout << "WARNING: eglDestroyContext failed." << std::endl;
        eglContext = EGL_NO_CONTEXT;
        return true;
    }
    else
    {
        eglContext = EGL_NO_CONTEXT;
        return true;
    }
}
