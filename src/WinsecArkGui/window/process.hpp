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
            static int select_row = -1;
            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"进程(Process)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
                    static ImGuiTableFlags flags =
                        ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;

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

                            ImGui::PopID();
                        }

                        ImGui::EndTable();
                    }


                    if (select_row != -1 && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
                    {
                        if (ImGui::BeginPopupContextWindow())
                        {
                            if (ImGui::Selectable(u8"菜单项"))
                            {
                                // 在这里处理菜单项的逻辑
                            }

                            ImGui::EndPopup();
                        }
                    }
                    ImGui::End();
                }
            }
        }
    }
}

