﻿#include "app.h"

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

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu(u8"File"))
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
            ImGui::MenuItem(u8"About", nullptr, &App::Dialog::About::isShow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}