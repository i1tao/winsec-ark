#pragma once

#include "command.hpp"
#include "imgui.h"


namespace App
{
    namespace Window
    {
        namespace ProcessWindow
        {
            static bool isOpen = true;
            static int select_row = -1;

            static char column_names[][16] = {
                u8"PID",
                u8"Name",
                u8"EPROCESS",
                u8"Path",
                u8"Description"
            };

            void Draw()
            {
                if (isOpen)
                {
                    ImGui::Begin(u8"进程(Process)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
                    static ImGuiTableFlags flags =
                        ImGuiTableFlags_RowBg
                        | ImGuiTableFlags_ContextMenuInBody
                        | ImGuiTableFlags_ScrollX
                        | ImGuiTableFlags_ScrollY
                        | ImGuiTableFlags_BordersOuter
                        | ImGuiTableFlags_BordersV
                        | ImGuiTableFlags_BordersH
                        | ImGuiTableFlags_Sortable
                        ;

                    if (ImGui::BeginTable("table_process", 6, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8)))
                    {
                        for (size_t i = 0; i < std::size(column_names); i++)
                        {
                            ImGui::TableSetupColumn(column_names[i], ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, i);
                        }
                        ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
                        ImGui::TableHeadersRow();
                        static float row_min_height = 0.0f;
                        for (int i = 0; i < 10; i++)
                        {
                            //const bool item_is_selected = (select_row == i);
                            ImGui::PushID(i);
                            ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                            ImGui::TableSetColumnIndex(0);
                            if (ImGui::Selectable("Index", select_row == i, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap, ImVec2(0, row_min_height)))
                            {
                                select_row = i;
                            }

                            if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
                            {
                                select_row = i;
                                ImGui::Text("This a popup for \"%d\"!", i);
                                if (ImGui::MenuItem(u8"结束进程"))
                                {
                                    int n = 9;
                                }
  /*                              if (ImGui::Button("Close"))
                                    ImGui::CloseCurrentPopup();*/
                                ImGui::EndPopup();
                            }

                            if (ImGui::TableNextColumn())
                                ImGui::Text("%d", i + 1);

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


                    ImGui::End();
                }
            }
        }
    }
}

