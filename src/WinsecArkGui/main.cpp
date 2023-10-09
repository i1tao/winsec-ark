#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" ) //hide consoles

#include "gui.hpp"


int main(int, char**)
{
    Gui::Run();

    return 0;
}
