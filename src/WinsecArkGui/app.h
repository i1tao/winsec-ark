#ifndef APP_H
#define APP_H

#include "imgui.h"

namespace App
{
    static bool g_isShowAbout = false;


    void DrawUI(unsigned int weight,unsigned int height);

    void DrawMenuBar();
    void DrawMainWindow(bool& isOpened);
    void DrawCommandWindow(bool& isOpened);
    void DrawTabs();


    void ShowAbout(bool* isShowAbout);
}

#endif

