#pragma once

#include "imgui.h"


namespace App
{
    namespace Dialog
    {
        namespace About
        {
            static bool isShow = false;

            inline void Draw()
            {
                if (isShow)
                {
                    if (!ImGui::Begin(g_Langueage ? u8"关于" : "About", &isShow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking))
                    {
                        ImGui::End();
                        return;
                    }

                    ImGui::Text(u8"Winsec Anti-Rookit Tool");
                    ImGui::Text(g_Langueage ? u8"一个简单、免费的开源 Anti-Rookit 工具":u8"A simple & free open source ARK");
                    ImGui::Text(u8"Author: i1tao");
                    ImGui::Text(u8"Github: https://github.com/i1tao/winsec-ark");
                    ImGui::Separator();
                    ImGui::Text(u8"Thanks for:");
                    ImGui::Text(u8"           IMGUI");
                    ImGui::Separator();
                    ImGui::Text(u8"Copyright © 2024 i1tao. All rights reserved.");

                    ImGui::End();
                }
            }
        }
    }
}
