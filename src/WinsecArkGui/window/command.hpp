#pragma once

#include <string>

#include "imgui.h"
namespace App
{
    namespace Window
    {
        namespace CommandWindow
        {
            static bool isOpen = true;
            //static char text[1024 * 16] =
            //    "/*\n"
            //    " Winsec Anti-Rookit load success !\n"
            //    "*/\n\n";

            static std::string text =
                "/*\n"
                " Winsec Anti-Rookit load success !\n"
                "*/\n\n";
            static char commands[256] = "";
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"Commands", &isOpen, ImGuiWindowFlags_AlwaysAutoResize);
                    ImGui::InputTextMultiline("##source", const_cast<char*>(text.c_str()),text.size(), ImVec2(-FLT_MIN, -FLT_MIN - 30), ImGuiInputTextFlags_ReadOnly);
                    ImGui::PushItemWidth(-120);
                    ImGui::InputTextWithHint("->", g_Langueage ? u8"«Î ‰»Î√¸¡Ó": u8"Please input your command", commands, 256);
                    ImGui::SameLine();
                    ImGui::Button(u8"÷¥––(Run)");
                    ImGui::SameLine();

                    ImGui::End();
                }
            }
        }
    }
}
