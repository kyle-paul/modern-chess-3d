#include <iostream>
#include "Core/Window/Window.h"
#include "Core/Debug/Logging.h"

int main()
{
    Logging::Init();

    Window window;
    window.Init();
    window.Run();

    INFO("finised");
}