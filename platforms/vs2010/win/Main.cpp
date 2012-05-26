#include "stdafx.h"

#include "Main.h"
#include "Platform.h"
#include "Opengl.h"
#include "Graphics.h"

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
    return Main::main(argc, argv);
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

int Main::main(int argc, _TCHAR* argv[])
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

    Core::init();

    /// Enter message loop.
    while (Core::run)
    {
        MSG Msg;
	    while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
	    {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
	    }
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        double totalElapsedSeconds = static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / timeCounterFrequency;
        Core::onMessageQueueEmpty(totalElapsedSeconds);
    }
    Core::shutdown();

    while (waitForConsoleToClose)
    {
        // Wait until user presses enter in console window.
    }

	ReleaseDC(Main::applicationWindowHandle, Main::deviceContext);
	return 0;
}

DWORD WINAPI Main::consoleThread(LPVOID lpParam)
{
    static char line[Core::maxLuaLineSize];
    while (Core::run)
    {
        if (Core::luaChunk == NULL)
        {
            fgets(line, Core::maxLuaLineSize, stdin);
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
    if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN || msg == WM_KEYUP || msg == WM_SYSKEYUP)
    {
        printf("WM_KEYDOWN\n");
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

/**
 * Initialize for OpenGL.
 */
void Main::initOpengl()
{
//	PIXELFORMATDESCRIPTOR pfd;
//	int format;
	
//	deviceContext = GetDC(applicationWindowHandle);
	

/*
	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(deviceContext, &pfd);
	SetPixelFormat(deviceContext, format, &pfd);
	
	renderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, renderContext); /// \todo Determine if we can make renderContext local to init()

    const GLubyte * openglVersion = glGetString(GL_VERSION);
    Graphics::checkOpenglError("Main::initOpengl glGetString Failed.");

    const GLubyte * openglExtensions = glGetString(GL_EXTENSIONS);
    Graphics::checkOpenglError("Main::initOpengl glGetString Failed.");

    if (strstr((const char *)openglExtensions, "GL_ARB_ES2_compatibility") == NULL)
    {
        Platform::fatalError("Your OpenGL driver does not support GL_ARB_ES2_compatibility");
    }
*/
//    Opengl::init();
}
