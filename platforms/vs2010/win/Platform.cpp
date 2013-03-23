#include "stdafx.h"
#include "Platform.h"
#include "Main.h"

unsigned int Platform::screenWidth = 300;
unsigned int Platform::screenHeight = 300;

void Platform::displayMessage(const std::string & msg)
{
    std::cout << msg << std::endl;
}

void Platform::fatalError(const std::string & msg)
{
#ifdef _DEBUG
    Main::waitForConsoleToClose = true;
#endif
    displayMessage(msg);
    Core::run = false;
}
