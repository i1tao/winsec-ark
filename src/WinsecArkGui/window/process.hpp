#pragma once

#include "imgui.h"


namespace App
{
    namespace Window
    {
        namespace ProcessWindow
        {


            static bool isOpen = true;
            static ImVector<int> selection;

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
                        | ImGuiTableFlags_SizingFixedFit| ImGuiTableFlags_ContextMenuInBody;

                    ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
                    if (ImGui::BeginTable("table_process", 6, flags, outer_size))
                    {
                        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
                        ImGui::TableSetupColumn(u8"Option", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"PID", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Name", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"EPROCESS", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Path", ImGuiTableColumnFlags_None);
                        ImGui::TableSetupColumn(u8"Description", ImGuiTableColumnFlags_None);
                        ImGui::TableHeadersRow();

                        static int select_row = -1;
                        static float row_min_height = 0.0f;
                        for (int i = 0; i < 10; i++)
                        {
                            const bool item_is_selected = (select_row == i);
                            ImGui::PushID(i);
                            ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);
                            
                            if (ImGui::TableSetColumnIndex(0))
                            {
                                if (ImGui::SmallButton(u8"op"))
                                {
                                    ImGui::OpenPopup("ContextMenu");

                                }

                            }
                            ImGui::TableNextColumn();
                            if (ImGui::Selectable("Index", item_is_selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2(0, row_min_height)))
                            {
                                if (item_is_selected)
                                {
                                    select_row = -1;
                                }
                                else
                                {
                                    select_row = i;
                                }
                            }

                            if (ImGui::TableNextColumn())
                                ImGui::Text("Data %d", i + 1);

                            if (ImGui::TableNextColumn())
                                ImGui::Text("Value %d", i + 1);

                            if (ImGui::TableNextColumn())
                                ImGui::Text("Item %d", i + 1);

                            if (ImGui::TableNextColumn())
                                ImGui::Text("Amount %d", i + 1);
                            
                            if (ImGui::BeginPopup("ContextMenu"))
                            {
                                if (ImGui::MenuItem("Edit"))
                                {
                                    // 在这里处理编辑操作
                                }
                                if (ImGui::MenuItem("Delete"))
                                {
                                    // 在这里处理删除操作
                                }
                                ImGui::EndPopup();
                            }
                            ImGui::PopID();
                        }

                        ImGui::EndTable();
                    }
                    ImGui::End();
                }
            }
        }
    }
}
