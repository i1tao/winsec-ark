#pragma once

#include "imgui.h"
namespace App
{
    namespace Window
    {
        namespace CommandWindow
        {
            static bool isOpen = true;
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"Commands", &isOpen, ImGuiWindowFlags_AlwaysAutoResize);

                    static char text[1024 * 16] =
                        "/*\n"
                        " Winsec Anti-Rookit load success !\n"
                        "*/\n\n";

                    ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, -FLT_MIN - 30), ImGuiInputTextFlags_ReadOnly);
                    static char str0[128] = "";
                    ImGui::PushItemWidth(-120);
                    ImGui::InputTextWithHint("->", u8"ÇëÊäÈëÃüÁî(Please input your command)", str0, 256); ImGui::SameLine();
                    ImGui::Button(u8"Ö´ĞĞ(Run)"); ImGui::SameLine();

                    ImGui::End();
                }
            }
        }
    }
}
