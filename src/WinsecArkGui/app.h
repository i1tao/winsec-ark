#ifndef APP_H
#define APP_H

#include "imgui.h"

namespace app
{
    enum app_language
    {
        english = 0,
        chinese = 1,
    };
    inline int g_select_language = app_language::english;


    void draw_ui(unsigned int weight, unsigned int height);
    void draw_menu_bar();

}

#endif

