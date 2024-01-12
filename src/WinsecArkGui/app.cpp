#include "app.h"

#include <map>
#include <vector>

#include "dialog/about.hpp"
#include "window/kernel.hpp"
#include "window/process.hpp"
#include "window/command.hpp"





void App::DrawUI(unsigned int weight, unsigned int height)
{
    DrawMenuBar();

    App::Window::ProcessWindow::Draw();
    App::Window::KernelModuleWindow::Draw();
    Window::CommandWindow::Draw();
    Dialog::About::Draw();
}

void App::DrawMenuBar()
{
    std::vector<std::vector<std::string>> vecMenuText =
    {
        {std::vector<std::string>{u8"File"  ,u8"文件"} },
        {std::vector<std::string>{u8"View"  ,u8"查看"} },
        {std::vector<std::string>{u8"Option",u8"选项"} },
        {std::vector<std::string>{u8"About" ,u8"关于"} },
    };
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu(vecMenuText[0][g_Langueage].c_str()))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(vecMenuText[1][g_Langueage].c_str()))
        {
            std::vector<std::vector<std::string>> vecViewText =
            {
                {std::vector<std::string>{u8"Process"         ,u8"进程窗口"} },
                {std::vector<std::string>{u8"Kernel Modules"  ,u8"内核模块"} },
                {std::vector<std::string>{u8"Option",u8"选项"} },
                {std::vector<std::string>{u8"About" ,u8"关于"} },
            };
            if (ImGui::MenuItem(vecViewText[0][g_Langueage].c_str())) {}
            if (ImGui::MenuItem(vecViewText[1][g_Langueage].c_str())) {}
            ImGui::Separator();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(vecMenuText[2][g_Langueage].c_str()))
        {
            if (ImGui::BeginMenu(!g_Langueage ? "Language" : u8"语言"))
            {
                if (ImGui::MenuItem(u8"English"))
                {
                    g_Langueage = 0;
                }
                if (ImGui::MenuItem(u8"中文"))
                {
                    g_Langueage = 1;
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            ImGui::MenuItem(vecMenuText[3][g_Langueage].c_str(), nullptr, &App::Dialog::About::isShow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}