#pragma once

#include "imgui.h"


namespace App
{
    namespace Dialog
    {
        namespace About
        {
            static bool isShow = false;
            void Draw()
            {
                if (isShow)
                {
                    if (!ImGui::Begin(u8"关于", &isShow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking))
                    {
                        ImGui::End();
                        return;
                    }

                    ImGui::Text(u8"Winsec Anti-Rookit Tool");
                    ImGui::Text(u8"一个简单、免费的开源 Anti-Rookit 工具");
                    ImGui::Text(u8"Author: i1tao");
                    ImGui::Text(u8"Github: https://github.com/i1tao/winsec-ark");
                    ImGui::Separator();
                    ImGui::Text(u8"Thanks for:");
                    ImGui::Text(u8"           IMGUI");
                    ImGui::Separator();
                    ImGui::Text(u8"Copyright © 2023 i1tao. All rights reserved.");

                    ImGui::End();
                }
            }
        }
    }
}
