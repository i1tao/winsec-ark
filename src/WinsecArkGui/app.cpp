#include "app.h"

#include "dialog/about.hpp"
#include "window/kernel.hpp"
#include "window/process.hpp"
#include "window/command.hpp"

void RenderUI()
{
    static bool isOpen = false;
    ImGui::Begin(u8"测试", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;

    if (ImGui::BeginTable("Table", 3, flags))
    {
        // 设置表头
        ImGui::TableSetupColumn("Column 1");
        ImGui::TableSetupColumn("Column 2");
        ImGui::TableSetupColumn("Column 3");
        ImGui::TableHeadersRow();

        // 添加表格内容
        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow();

            for (int column = 0; column < 3; column++)
            {
                ImGui::TableSetColumnIndex(column);

                // 在每一行的每一列中绘制内容
                ImGui::Text("Row %d, Column %d", row, column);

                // 检查鼠标是否悬停在某一行上
                if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    // 选中整行
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + row, ImGui::GetColorU32(ImGuiCol_HeaderActive));
                }
            }
        }

        ImGui::EndTable();
    }

    // 右键菜单
    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Selectable("菜单项"))
        {
            // 在这里处理菜单项的逻辑
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

void App::DrawUI(unsigned int weight, unsigned int height)
{

    DrawMenuBar();

    App::Window::ProcessWindow::Draw();
    App::Window::KernelModuleWindow::Draw();
    Window::CommandWindow::Draw();
    Dialog::About::Draw();

    RenderUI();

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