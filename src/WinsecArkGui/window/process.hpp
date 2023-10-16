#pragma once

#include "imgui.h"


namespace App
{
    namespace Window
    {
        namespace ProcessWindow
        {
            static bool isOpen = true ;
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"½ø³Ì(Process)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
                    static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX
                        | ImGuiTableFlags_ScrollY
                        | ImGuiTableFlags_RowBg
                        | ImGuiTableFlags_BordersOuter
                        | ImGuiTableFlags_BordersV
                        | ImGuiTableFlags_Resizable
                        | ImGuiTableFlags_Reorderable
                        | ImGuiTableFlags_Hideable
                        | ImGuiTableFlags_Sortable
                    |ImGuiTableFlags_SortMulti;

                    ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
                    if (ImGui::BeginTable("table_process", 5, flags, outer_size))
                    {
                        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
                        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("EPROCESS", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_None);
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
                                    ImGui::Text("%d Hello %d,%d          ", row, column, row);
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
