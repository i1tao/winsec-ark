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
                    ImGui::Begin(u8"进程(Process)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
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
                        ImGui::TableSetupColumn(u8"PID", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Name", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"EPROCESS", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Path", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Description", ImGuiTableColumnFlags_None);
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

                                    if (ImGui::IsItemHovered()) {
                                        // 在悬停时可以高亮当前行
                                        //ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg1, ImGui::GetColorU32(ImGuiCol_TableRowBgHovered));
                                    }

                                    // 使用 IsItemClicked() 检测项目是否被点击
                                    if (ImGui::IsItemClicked()) {
                                        // 在这里可以处理选中该项目的逻辑，例如，记录选中的项目或执行某些操作
                                        //selected_item = i;
                                    }
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
