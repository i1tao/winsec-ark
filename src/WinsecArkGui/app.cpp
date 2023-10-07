#include "app.h"

#include "imgui_internal.h"

void App::DrawUI(unsigned int weight, unsigned int height)
{
    //Draw main window
    static bool isMainWindowOpen = false;
    static bool isOutputWindowOpen = false;

    //DrawMenuBar();

    ImGui::Begin(u8"MainWindow", &isMainWindowOpen,ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoTitleBar);
    ImGui::BeginTabBar("##tabs");
    if (ImGui::BeginTabItem(u8"进程(Process)"))
    {

        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem(u8"驱动(Drivers)"))
    {

        ImGui::EndTabItem();
    }
    
    ImGui::EndTabBar();
    ImGui::End();

    ImGui::Begin(u8"OutPut", &isOutputWindowOpen, ImGuiWindowFlags_AlwaysAutoResize);

    static char text[1024 * 16] =
        "/*\n"
        " Winsec Anti-Rookit load success !\n"
        "*/\n\n";

    ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_ReadOnly);

    ImGui::End();

    ImGui::Begin(u8"Command", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    static char str0[128] = u8"请输入命令";
    ImGui::InputText("->", str0,64); ImGui::SameLine();
    ImGui::Button(u8"执行"); ImGui::SameLine();
    ImGui::End();
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
