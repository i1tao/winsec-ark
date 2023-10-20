#pragma once

#include "imgui.h"


namespace App
{
    namespace Window
    {
        namespace ProcessWindow
        {


            static bool isOpen = true ;
            static bool selectedRow[10] = { false };
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"进程(Process)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
                    static ImGuiTableFlags flags =
                        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
                        | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
                        | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
                        | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
                        | ImGuiTableFlags_SizingFixedFit;

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

                        static int selectedRow = -1;
                        // Demonstrate using clipper for large vertical lists
                        for (int i = 0; i < 10; i++)
                        {
                            ImGui::TableNextRow();

                            ImGui::TableSetColumnIndex(0);

                            ImGui::Selectable("Index", selectedRow == i, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2(0, 0));
                            ImGui::TableNextColumn();
                            ImGui::Text("Data %d", i + 1);

                            ImGui::TableNextColumn();
                            ImGui::Text("Value %d", i + 1);

                            ImGui::TableNextColumn();
                            ImGui::Text("Item %d", i + 1);

                            ImGui::TableNextColumn();
                            ImGui::Text("Amount %d", i + 1);

                            // 监听行是否被点击并选中

                            //if (ImGui::IsItemClicked(0))
                            //{
                            //    selectedRow = i;
                            //}
                            ////if (ImGui::Selectable("label", selectedRow, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2(0, 0)))
                            ////{
                            ////    selectedRow = i;
                            ////}

                            //if (selectedRow == i)
                            //{
                            //    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(0, 100, 0, 255));
                            //}
                        }
                        
                        // 判断当前行是否被选中，若是，设置高亮颜色
                        
                        ImGui::EndTable();
                    }
                    ImGui::End();
                }
            }
        }
    }
}
