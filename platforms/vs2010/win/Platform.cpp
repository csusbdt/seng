#include "stdafx.h"
#include "Platform.h"
#include "Main.h"

unsigned int Platform::screenWidth = 300;
unsigned int Platform::screenHeight = 300;

void Platform::swapBuffers()
{
    SwapBuffers(Main::deviceContext);
}

void Platform::displayMessage(const std::wstring & msg)
{
    MessageBoxW(0, msg.c_str(), L"Message", MB_OK);
}

void Platform::displayMessage(const std::string & msg)
{
    MessageBoxA(0, msg.c_str(), "Message", MB_OK);
}

void Platform::fatalError(const std::wstring & msg)
{
    displayMessage(msg);
    exit(1);
}

void Platform::fatalError(const std::string & msg)
{
    displayMessage(msg);
    exit(1);
}
