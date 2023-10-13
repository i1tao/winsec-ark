#include "app.h"

#include "imgui_internal.h"

void App::DrawMainWindow(bool& isOpened)
{
    ImGui::Begin(u8"进程(Process)", &isOpened, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX
        | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg
        | ImGuiTableFlags_BordersOuter
        | ImGuiTableFlags_BordersV
        | ImGuiTableFlags_Resizable
        | ImGuiTableFlags_Reorderable
        | ImGuiTableFlags_Hideable
        | ImGuiTableFlags_Sortable;

    ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
    if (ImGui::BeginTable("table_process", 4, flags, outer_size))
    {
        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Eprocess", ImGuiTableColumnFlags_None);
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
                    ImGui::Text("%d Hello %d,%d          ", row, column, row);
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
    static bool isOpen = NULL;
    ImGui::Begin(u8"内核模块(Kernel module)", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
     flags = ImGuiTableFlags_ScrollX
        | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg
        | ImGuiTableFlags_BordersOuter
        | ImGuiTableFlags_BordersV
        | ImGuiTableFlags_Resizable
        | ImGuiTableFlags_Reorderable
        | ImGuiTableFlags_Hideable
        | ImGuiTableFlags_Sortable;

    outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
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

void App::DrawCommandWindow(bool& isOpened)
{
    ImGui::Begin(u8"Commands", &isOpened, ImGuiWindowFlags_AlwaysAutoResize);

    static char text[1024 * 16] =
        "/*\n"
        " Winsec Anti-Rookit load success !\n"
        "*/\n\n";

    ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, -FLT_MIN - 30), ImGuiInputTextFlags_ReadOnly);
    static char str0[128] = "";
    ImGui::PushItemWidth(-120);
    ImGui::InputTextWithHint("->", u8"请输入命令(Please input your command)", str0, 256); ImGui::SameLine();
    ImGui::Button(u8"执行(Run)"); ImGui::SameLine();

    ImGui::End();
}

void App::DrawUI(unsigned int weight, unsigned int height)
{
    //Draw main window
    static bool isMainWindowOpen = false;
    static bool isCommandWindowOpen = false;

    DrawMenuBar();

    DrawMainWindow(isMainWindowOpen);
    DrawCommandWindow(isCommandWindowOpen);


    //DrawTabs();


    if (g_isShowAbout)
    {
        ShowAbout(&g_isShowAbout);
        //ImGui::ShowAboutWindow(&g_isShowAbout);
    }
}

void App::DrawMenuBar()
{

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"查看"))
        {
            if (ImGui::MenuItem(u8"进程窗口")) {}
            if (ImGui::MenuItem(u8"Redo")) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem(u8"Cut")) {}
            if (ImGui::MenuItem(u8"Copy")) {}
            if (ImGui::MenuItem(u8"Paste")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"关于"))
        {
            ImGui::MenuItem("About", nullptr, &g_isShowAbout);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void App::DrawTabs()
{

    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        ImGui::Button("hello");
        if (ImGui::BeginTabItem(u8"进程(Process)"))
        {

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void App::ShowAbout(bool* isShowAbout)
{
    if (!ImGui::Begin(u8"关于", isShowAbout, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking))
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
