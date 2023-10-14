#pragma once

#include "imgui.h"


namespace App
{
    namespace Window
    {
        namespace KernelModuleWindow
        {
            static bool isOpen = true;
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"ÄÚºËÄ£¿é(Kernel module)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
                    auto flags = ImGuiTableFlags_ScrollX
                        | ImGuiTableFlags_ScrollY
                        | ImGuiTableFlags_RowBg
                        | ImGuiTableFlags_BordersOuter
                        | ImGuiTableFlags_BordersV
                        | ImGuiTableFlags_Resizable
                        | ImGuiTableFlags_Reorderable
                        | ImGuiTableFlags_Hideable
                        | ImGuiTableFlags_Sortable;

                    auto outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
                    if (ImGui::BeginTable("table_kernel", 5, flags, outer_size))
                    {
                        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
                        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Base", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Load Order", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_None);
                        ImGui::TableHeadersRow();

                        // Demonstrate using clipper for large vertical lists
                        ImGuiListClipper clipper;
                        clipper.Begin(5);
                        while (clipper.Step())
                        {
                            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                            {
                                ImGui::TableNextRow();
                                for (int column = 0; column < 3; column++)
                                {
                                    ImGui::TableSetColumnIndex(column);
                                    ImGui::Text("1%d Hello %d,%d          ", row, column, row);
                                }
                            }
                        }
                        ImGui::EndTable();
                    }
                    ImGui::End();
                }
            }
        }
    }
}
